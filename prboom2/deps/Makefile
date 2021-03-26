PREFIX=$(HOME)/.local
export PREFIX := $(PREFIX)

blank :=
define NEWLINE

$(blank)
endef

file := rust/config.toml

all: rust

rust: clean $(PREFIX)/bin/cargo

$(PREFIX)/bin/cargo: $(file)
	cd rust && git submodule update --init --recursive && git checkout 1.51.0 && python x.py build --stage 2 && python x.py install cargo

$(file):
	$(file > $@,[build]$(NEWLINE)docs = false)

clean:
ifeq ($(OS),Windows_NT)
	powershell -command 'Remove-Item -Verbose "$(file)" -ErrorAction SilentlyContinue; exit 0'
else
	rm -vf "$(file)"
endif
