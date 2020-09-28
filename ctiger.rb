
class ctiger < Formula
    desc "power tool for requests"
    homepage "https://ctiger.github.io"
    url "https://github.com/Sandieps/homebrew-ctiger/archive/1.0.tar.gz"
    def install
        system "cmake", "./"
        system "make"
        system "make", "install"
        end
    end
end
