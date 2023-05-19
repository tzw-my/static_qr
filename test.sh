# shellcheck    shell=bash    disable=SC2039,3043,2012,2013,2086,2154
x log init pkg_test
git clone https://github.com/x-cmd/pkg.git
x pkg update
printf "%s\n" "| 软件名 | 软件运行path | 异常 | 错误信息 |" >> ./ret.md
printf "%s\n" "| :----: | :----: | :----: | :----: |" >> ./ret.md
ls pkg/src/osman | for pkg_bin in $(cat); do
  url="$( ___x_cmd_pkg___list "${pkg_bin}" "v0.0.0" "$os_name" "url.internet" )"
  pkg_test:info "========================${pkg_bin}===================="
  curl -LO "$url"
  x uz "${url##*/}" "./${pkg_bin}_dir/"

  bin_name="$(___x_cmd_pkg___list "${pkg_bin}" "v0.0.0" "$os_name" "xbin.${pkg_bin}")"
  [ -z "$bin_name" ] && bin_name="$(___x_cmd_pkg___list "${pkg_bin}" "v0.0.0" "$os_name" "xbin" | { read -r line ; printf "%s\n" "$line" ;} )"
  bin_path="$(find ./${pkg_bin}_dir -name "${bin_name##*/}" -type f )"
  chmod +x "$bin_path"
  $bin_path --help 1>/dev/null 2>log || {
    pkg_test:error "bin test failed: ${bin_name##*/},path : $bin_path"
    printf "%s\n" "| ${pkg_bin} | ${bin_path} | ❌ | $(cat log) |" >> ./ret.md
  }
done
cat ./ret.md