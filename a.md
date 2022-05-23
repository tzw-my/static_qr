### 目标1:统一编译环境 
####  思考问题:
1. 统一编译环境的理由？
    1. **可复现**:所有软件在同一个container中重复编译都能得到与第一次相同的sha256,避免环境干扰。
    2. **加快编译**:预先将高频使用的依赖提前安装，减少人工编译步骤。
    3. **复用性**:相同依赖的APP,编译环境可以共享
    PS:github actions里面已经安装了各种编译环境。如果APP没有需要编译的依赖，似乎没必要用container

2. 怎么才算统一编译环境？<br>
**总结**：从下列表格上看，以系统及语言划分似乎比较合理。
- 构建基础镜像，安装好初始依赖？这里的初始依赖如何定义？例如:<br>
container 中安装基本编译环境(已有curl/wget/git)<br>
CLib===gcc,g++,make,automake,libtool(CLib替代gcc,g++,make,automake,libtool)

| language | windows |linux/macOs |
| ---------- | -------- | ------- |
| C |mingw64,make,automake| CLib |
| Go|go|go|

| static-build | 预装软件 | 依赖项 | 特殊裁剪 |
| ------------ | ------- | ----- |  -------- |
| tessaract    |  |  leptonica | linux 和 mac自带tessaract |
| curl         | CLib | libressl,zlib,libhttp2 | / |
| yq           |   go | / |  /  |
| 7za          | CLib | / | 需要修改源码 |
| tmux         | CLib | libevent,ncurses,pkg-config | / |
| qrcode       | CLib | pkg-config | / |
| dot          | CLib | pkg-config | / |
| imagemagick  | CLib | / | / |
| smartmontools| CLib | linux/bsg.h | make 需要修改Makefile.am |
| nmap         | CLib | openssl | / |
| FFmpeg       | CLib | libass,nasm,x265,libvpx,fdk-aac,opus,aom,SVT-AV1,libdav1d,libvmaf | / |

 3. 如果需要初始化环境，需要多少个初始化环境？
 - 按照目前APP数量及依赖统计来看，只需要每个系统一个即可。
 - 可以提前将依赖编译好，需要时直接下载。或者将依赖的编译脚本放到container中build.

 4. app如何对应到不同的编译环境中？
 - 按语言分类？还是直接按依赖分？
 - 有指定lib版本的需要独立创建一个镜像？
### 目标2：自动化编译
1. 自动化能简化哪些步骤？
- 主要为了后期维护更新

2. 需要修改代码才能正常build的app如何自动化？
- 使用代码替换的方式不太合理，可能替换到别的内容。且版本更新时需要替换的代码行数也可能发生变化。