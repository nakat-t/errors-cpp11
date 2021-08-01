import argparse
import pathlib
import textwrap
import yaml

# リポジトリルートパスを返す
def repos_root_path():
    return pathlib.Path(__file__).resolve().parent.parent

# cmake 用リストを出力する
def do_update_globs_cmake(lists, dir, output):
    output_file = pathlib.Path(dir).joinpath(output["name"])
    with open(output_file, mode='w', encoding='UTF-8') as f:
        for l in lists:
            print("set(", file=f)
            print("    {}".format(l["name"]), file=f)
            for expand in l["__expand__"]:
                print("    \"{}\"".format(expand.as_posix()), file=f)
            print(")", file=f)

# yml_obj["lists"][N]["glob"] の内容を展開して yml_obj["lists"][N]["__expand__"] に格納する
def expand_globs(yml_obj, dir):
    for l in yml_obj["lists"]:
        expand_set = set([])
        for glob in l["glob"]:
            if isinstance(glob, str):
                for expand in pathlib.Path(dir).glob(glob):
                    expand_set.add( expand.resolve().relative_to(repos_root_path()) )
            if isinstance(glob, dict):
                if "include" in glob:
                    for expand in pathlib.Path(dir).glob(glob["include"]):
                        expand_set.add( expand.resolve().relative_to(repos_root_path()) )
                if "exclude" in glob:
                    for expand in pathlib.Path(dir).glob(glob["exclude"]):
                        expand_set = set([x for x in expand_set if x != expand.resolve().relative_to(repos_root_path())])
        l["__expand__"] = sorted(expand_set)

# update_globs コマンドを実行する
def update_globs():
    # カレントディレクトリ以下の全ての *.lists.yml に対して処理する
    for lists_yml in pathlib.Path(".").glob("**/*.lists.yml"):
        with open(lists_yml) as f:
            yml_obj = yaml.safe_load(f)
            dir = lists_yml.resolve().parent # lists.yml ファイルがあるディレクトリ

            expand_globs(yml_obj, dir)

            # yml_obj["output"] の内容に従って lists を書式変換＆ファイル出力する
            for output in yml_obj["output"]:
                # cmake 出力
                if output["type"] == "cmake":
                    do_update_globs_cmake(yml_obj["lists"], dir, output)


def main():
    parser = argparse.ArgumentParser(
        formatter_class=argparse.RawTextHelpFormatter,
        description=textwrap.dedent('''
            リストファイル (*.lists.yml) の glob を展開して実ファイルパスのリストに変換します。
            '''
        )
    )
    args = parser.parse_args()
    update_globs()

if __name__ == "__main__":
    main()
