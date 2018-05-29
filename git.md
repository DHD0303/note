# Git  
### remote  
* 对远程仓库的一些操作  
```
git remote add [主机] [网址] //连接远端仓库
git remote show [主机] //显示详细信息
git remote rm [主机] //删除远端仓库
git remote rename [原主机名] [新主机名] //更改主机名
```
### add  
* 提交工作区更改到暂存区  
```
git add . //.为通配符，表示提交所有更改
git add [file] //表示提交某个文件
```  
### commit  
* 记录对仓库的更改  
```
git commit -m "note" //最好在后面加上-m参数描述这个更改
```
* 指定一个未来时间
```
git commit --date=05.29.2018T14:00:00//格式(月 日 年)T(24小时制时间)
```
### push  
* 推送暂存区的文件到远端仓库  
```
git push [主机(可缺省)] [分支(可缺省)]
```  
* 推送仓库到远端  
```
git push [远端仓库] [本地分支]:[远端分支(可缺省)]
```
> 可缺省的前提是，你的本地仓库已经绑定了远端仓库  

* 推送本地tag到远端仓库  
```
git push --tags [主机] [分支]
```
### clong  
* 复制一个远端仓库 可以指定文件夹  
* 示例  
```
clone [url]
clone [url] [path]
```
### .gitignore  
* 这不是一个命令，该文件在根目录下面，表示提交时忽略的文件，可以用通配符*，还支持!,如：  
```
*.htm
!index.html
```  
* 代表不上传除了index.html以外的所有.html文件  
### stasus  
* 查看仓库的状态  
### rm  
* 可以有参数 --cache -f，其中 -cache是从暂存区删除，而 -f 是从硬盘一同删除  
### stash  
* 储藏：暂存修改而不提交，用stash list查看所有的储藏  
* 参考
> https://git-scm.com/book/zh/v1/Git-%E5%B7%A5%E5%85%B7-%E5%82%A8%E8%97%8F%EF%BC%88Stashing%EF%BC%89  

### log  
* 可以查看所有的提交  
### tag  
* 可以对某个时间的版本打标签
```
git tag v1.0.0  打上版本号
git tag -l 可以查看当前有的所有标签，可以在后面加参数
git tag -l "1.0.*" 参数可以使用通配符
```  
### reset  
* 撤销提交  
* --soft 缓存区和工作区不会改变
* --mixed 默认， 使缓存区和远端库撤回  
* --hard 工作区，缓存区，远端库同时撤回  
```
git reset --soft HEAD^1 //撤回到上一次提交, HEAD^2则是上两次
```  
> 参考：https://github.com/geeeeeeeeek/git-recipes/wiki/5.2-%E4%BB%A3%E7%A0%81%E5%9B%9E%E6%BB%9A%EF%BC%9AReset%E3%80%81Checkout%E3%80%81Revert-%E7%9A%84%E9%80%89%E6%8B%A9  

### checkout  
* 检出  
```
git checkout [-q] [<commit>] [--] <paths>
省略commit则直接等于用上一次提交的文件覆盖工作区的文件
```  
* 切换分支  
```
git checkout -b [分支名]  //创建分支并转移
git checkout [分支] //转移到该分支
git checkout tags/[tag_name] //转移到特点的tag值的分支,如果tag——name没有和某个分支重名，则可以不加(tags/)
```

> 还有很多用法，以后遇到了再补，参照  
https://www.cnblogs.com/craftor/archive/2012/11/04/2754147.html  

### pull  
* 拉取远端仓库  
```
git pull [远程主机] [远程分支]:[本地分支(如果是当前分支，则该参数可以省去)]
```    
### rebase  
* 合并分支的一种方式  
```
git rebase [主机(可省略)] [分支]
```  
* 参考  
> https://git-scm.com/book/zh/v2/Git-%E5%88%86%E6%94%AF-%E5%8F%98%E5%9F%BA  

### diff  
* 查看操作  
```
git diff 工作区和暂存区
git diff --cached 远程库和暂存区
git diff HEAD 工作区和远程库
```  
> 参考  https://www.jianshu.com/p/80542dc3164e

### branch  
* 分支管理  
```
git branch [分支名]  创建分支
git branch 显示分支,前面有 * 号的为当前所在分支
```
### 一些远程操作  
> http://www.ruanyifeng.com/blog/2014/06/git_remote.html