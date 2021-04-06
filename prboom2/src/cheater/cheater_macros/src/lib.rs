use proc_macro::TokenStream;
use proc_macro2::Punct;
use proc_macro2::Spacing;
use proc_macro2::TokenTree;
use quote::quote;
use quote::format_ident;
use quote::ToTokens;
use syn::buffer::Cursor;
use syn::parse::Parse;
use syn::parse::ParseStream;
use syn::parse::StepCursor;
use syn::parse_macro_input;
use syn::Ident;
use syn::Lit;
use syn::LitStr;

fn take_cheat_name(input: ParseStream) -> syn::Result<String> {
    input.parse::<LitStr>().map(|s| s.value())
}

fn take_fat_arrow(input: ParseStream) -> syn::Result<()> {
    let generic_error = "expected `=>` after cheat name";
    input.step(|cursor: StepCursor| {
        let (eq, next) = cursor.punct().ok_or_else(|| cursor.error(generic_error))?;
        if eq.as_char() != '=' {
            return Err(cursor.error(generic_error));
        }
        match eq.spacing() {
            Spacing::Alone => return Err(cursor.error(generic_error)),
            Spacing::Joint => {}
        }
        let (gt, next) = next.punct().ok_or_else(|| cursor.error(generic_error))?;
        if gt.as_char() != '>' {
            return Err(cursor.error(generic_error));
        }
        match gt.spacing() {
            Spacing::Alone => {}
            Spacing::Joint => return Err(cursor.error(generic_error)),
        }
        Ok(((), next))
    })
}

fn take_cheat_fn_ident(input: ParseStream) -> syn::Result<Ident> {
    input.parse::<Ident>()
}

struct CheckCheatParamInput {
    cheat_name: String,
    cheat_fn_name: Ident,
}

impl Parse for CheckCheatParamInput {
    fn parse(input: ParseStream) -> syn::Result<Self> {
        let cheat_name = take_cheat_name(input)?;
        take_fat_arrow(input)?;
        let cheat_fn_name = take_cheat_fn_ident(input)?;
        Ok(Self {
            cheat_name,
            cheat_fn_name,
        })
    }
}

#[proc_macro]
pub fn check_cheat_param(input: TokenStream) -> TokenStream {
    let CheckCheatParamInput {
        cheat_name,
        cheat_fn_name,
    } = parse_macro_input!(input as CheckCheatParamInput);

    let fn_name = format_ident!("check_{}_cheat", cheat_name);
    (quote! {
        pub unsafe fn #fn_name() -> bool {
            let_cxx_string!(cheat = concat!("-", #cheat_name));
            if ffi::M_CheckParm(&cheat) != 0 {
                ffi::#cheat_fn_name();
                return true;
            }

            false
        }
    })
    .into()
}
