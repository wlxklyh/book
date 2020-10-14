# mac+hexo+githubpage博客

## 1、安装brew
参考：https://zhuanlan.zhihu.com/p/90508170
/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"

## 1、安装nodejs
参考：https://www.jianshu.com/p/3b30c4c846d1
brew link node
brew uninstall node
brew install node

## 3、安装npm
参考：https://www.jianshu.com/p/39b4339a9b60
sudo npm install npm -g

## 4、安装hexo
参考：https://zhuanlan.zhihu.com/p/75438236
npm install -g hexo-cli

## 5、拉去博客仓库
https://github.com/wlxklyh/MyBlog

## 6、本地预览
hexo g
hexo d
hexo server

## 7、提交到github 会拉起travis构建
https://travis-ci.org/

## 8、travis里面要设置仓库的提交token


## 9、最终效果
https://wlxklyh.github.io/