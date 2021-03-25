PREFIX=$(HOME)/.local
export PREFIX := $(PREFIX)

all: rust

rust: $(PREFIX)/bin/cargo

$(PREFIX)/bin/cargo:
	rust/x.py build --stage 2 && rust/x.py install cargo

rust/config.toml:
	echo -e "[llvm]\ndownload-ci-llvm = true\noptimize = true\n[build]\ndocs = false" > rust/config.toml

clean:
	rm -vf rust/config.toml
