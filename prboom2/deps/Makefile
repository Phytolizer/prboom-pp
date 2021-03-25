PREFIX=$(HOME)/.local
export PREFIX := $(PREFIX)

blank :=
define NEWLINE

$(blank)
endef

all: rust

rust: $(PREFIX)/bin/cargo

$(PREFIX)/bin/cargo: rust/config.toml
	cd rust && python x.py build --stage 2 && python x.py install cargo

rust/config.toml:
	$(file > rust/config.toml,[llvm]$(NEWLINE)download-ci-llvm = true$(NEWLINE)[build]$(NEWLINE)docs = false)

clean:
	rm -vf rust/config.toml
