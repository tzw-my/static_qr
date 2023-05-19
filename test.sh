# shellcheck    shell=bash    disable=SC2039,3043,2012,2013,2086,2154
x log init pkg_test
git clone https://github.com/x-cmd/pkg.git
x pkg update
ls pkg/src/osman | for pkg_bin in $(cat); do
  url="$( ___x_cmd_pkg___list "${pkg_bin}" "v0.0.0" "$os_name" "url.internet" )"
  pkg_test:info "========================${pkg_bin}===================="
  curl -LO "$url"
  x uz "${url##*/}" "./${pkg_bin}_dir/"

  bin_name="$(___x_cmd_pkg___list "${pkg_bin}" "v0.0.0" "$os_name" "xbin.${pkg_bin}")"

  bin_path="$(find ./${pkg_bin}_dir -name "${bin_name}")"
  chmod +x "$bin_path"
  $bin_path --help || {
    pkg_test:error "bin test failed: ${bin_name},path : $bin_path"
    printf "%s\n" "| ${bin_name} | ❌ |" >> ./ret.md
  }
done
cat ./ret.md