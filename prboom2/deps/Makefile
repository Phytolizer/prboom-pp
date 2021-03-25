PREFIX=$(HOME)/.local
export PREFIX := $(PREFIX)

all: rust

rust: $(PREFIX)/bin/cargo

$(PREFIX)/bin/cargo:
	rust/x.py build && rust/x.py install cargo

rust/config.toml:
	echo -e "[llvm]\noptimize = true\n[build]\ndocs = false" > rust/config.toml

clean:
	rm -vf rust/config.toml
