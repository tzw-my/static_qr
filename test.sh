# shellcheck    shell=bash    disable=SC2039,3043,2012,2013,2086,2154
x log init pkg_test
git clone https://github.com/x-cmd/pkg.git
x pkg update
printf "%s\n" "| 软件名 | 软件运行path | 异常 | 错误信息 |" >> ./ret.md
printf "%s\n" "| :----: | :----: | :----: | :----: |" >> ./ret.md
ls pkg/src/osman | for pkg_bin in $(cat); do
  [ "$pkg_bin" = "proot-rs" ] && pkg_bin=proot
  url="$( ___x_cmd_pkg___list "${pkg_bin}" "v0.0.0" "$os_name" "url.internet" )"
  pkg_test:info "========================${pkg_bin}===================="
  curl -LO "$url"
  x uz "${url##*/}" "./${pkg_bin}_dir/"
  bin_name="$(___x_cmd_pkg___list "${pkg_bin}" "v0.0.0" "$os_name" "xbin" | { read -r line ; printf "%s\n" "$line" ;} )"
  [ -z "$bin_name" ] && bin_name="$(___x_cmd_pkg___list "${pkg_bin}" "v0.0.0" "$os_name" "xbin.${pkg_bin}")"
  bin_path="$(find ./${pkg_bin}_dir -name "${bin_name##*/}" -type f )"
  chmod +x "$bin_path"

  [ "$pkg_bin" = "tmux" ] && {
    $bin_path -V 1>/dev/null 2>log || {
      pkg_test:error "bin test failed: ${bin_name##*/},path : $bin_path"
      printf "%s\n" "| ${pkg_bin} | ${bin_path} | ❌ | $(cat log) |" >> ./ret.md
    }
    continue
  }

  [ "$pkg_bin" = "sqlean" ] && {
    continue
  }
  
  [ "$pkg_bin" = "trdsql" ] && {
    $bin_path -version 1>/dev/null 2>log || {
      pkg_test:error "bin test failed: ${bin_name##*/},path : $bin_path"
      printf "%s\n" "| ${pkg_bin} | ${bin_path} | ❌ | $(cat log) |" >> ./ret.md
    }
    continue
  }

    [ "$pkg_bin" = "sodium" ] && {
    $bin_path base64encode hi 1>/dev/null 2>log || {
      pkg_test:error "bin test failed: ${bin_name##*/},path : $bin_path"
      printf "%s\n" "| ${pkg_bin} | ${bin_path} | ❌ | $(cat log) |" >> ./ret.md
    }
    continue
  }

  [ "$pkg_bin" = "kube-score" ] && {
    $bin_path version 1>/dev/null 2>log || {
      pkg_test:error "bin test failed: ${bin_name##*/},path : $bin_path"
      printf "%s\n" "| ${pkg_bin} | ${bin_path} | ❌ | $(cat log) |" >> ./ret.md
    }
    continue
  }

  $bin_path --help 1>/dev/null 2>log || {
    pkg_test:error "bin test failed: ${bin_name##*/},path : $bin_path"
    printf "%s\n" "| ${pkg_bin} | ${bin_path} | ❌ | $(cat log) |" >> ./ret.md
  }
done
cat ./ret.md

proot-rs 



