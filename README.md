# cpp_train

WSLでC++の勉強をする

## WSLの準備

### Gitの設定

#### Gitのインストール

Gitをインストールする．最初から入ってる場合が多いけど念のため．

```console
sudo apt update
sudo apt install git
```

#### Gitの設定

インストールが完了したら，ユーザーネーム，メールアドレス，エディタの設定を行う．  
ユーザー名とメールアドレスは半角アルファベットで入力，ダブルクォーテーションで囲む．
ユーザー名はGitHubのユーザー名と同じものを使う．

```console
git config --global user.name "ユーザー名"
git config --global user.email "メールアドレス"
git config --global core.editor 'vim -c "set fenc=utf-8"'
```

#### GitHubとの接続

Gitの設定が終わったら，GitHubに鍵を登録する．

`ssh-keygen`コマンドで鍵を生成する．
ここでは，鍵の名前を`id_rsa_github`としている．  
`-f`オプションを使用することで，鍵の名前を変更することができる．

```console
ssh-keygen -t rsa -b 4096 -f id_rsa_github
```

但し，`-f`オプションを使用すると鍵はカレントディレクトリに置かれてしまう．
SSHの鍵は`/.ssh`ディレクトリに置かれている必要があるので，`ssh-keygen`コマンドを使う際は`~/.ssh`ディレクトリに移動してから実行しなければならない．
`~/.ssh`ディレクトリが無い場合は，`mkdir`コマンドで作ればOK.
または，`-f`オプションを使用せずに`ssh-keygen`コマンドを実行すると`~/.ssh`ディレクトリを自動生成してくれるので，空の鍵を作って`~/.ssh`ディレクトリを作成しても良い．

鍵を生成したら，公開鍵(`.pub`拡張子が付いている方)の中身をGitHubに登録する．

GitHubのページの[Settingページ](https://github.com/settings/profile)->「SSH and GPG keys」メニュ->「New SSH Key」ボタンをクリック．  
「Title」に適当な名前を，「Key」に公開鍵の中身を全てコピーして入力する．
公開鍵の中身は，`cat`コマンドを使用してターミナルに表示するか，適当なテキストエディタで開いて表示し，コピーすればよい．

```console
cat ~/.ssh/id_rsa_github
```


入力が完了したら「Add SSH Key」ボタンをクリックして登録する．

最後に，SSHのコンフィグファイルを設定する．

コンフィグファイルが無いと，SSH接続を行う際，`~/.ssh`ディレクトリ内にあるデフォルト名の鍵(`id_rsa`)しか参照してくれない．
GitHub用に鍵の名前を変更しているので，このままでは接続することができない．

そこで，`~/.ssh`ディレクトリに`config`という名前のファイル(拡張子無し)を作成し，以下のように記述する．

```generic
# Github
Host github github.com
  HostName github.com
  IdentityFile ~/.ssh/id_rsa_github
  User git
```

このように記述することで，GitHubへのSSH接続の際に`id_rsa_github`を参照してくれるようになる．

GitHubにSSH接続できるかどうかは，次のコマンドを実行することで確認できる．

```console
ssh -T github
```

最初に接続するときは`known_host`にGitHubが無いので，GitHubを`known_host`に追加するかどうかを聞かれる．`yes`と入力して追加する．
