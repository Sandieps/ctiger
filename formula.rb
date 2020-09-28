def install
    mkdir "build" do
        system "cmake", "./"
        system "make"
        system "make", "install"
    end
end
