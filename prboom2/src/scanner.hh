// Copyright (c) 2010, Braden "Blzut3" Obrzut <admin@maniacsvault.net>
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//    * Redistributions of source code must retain the above copyright
//      notice, this list of conditions and the following disclaimer.
//    * Redistributions in binary form must reproduce the above copyright
//      notice, this list of conditions and the following disclaimer in the
//      documentation and/or other materials provided with the distribution.
//    * Neither the name of the <organization> nor the
//      names of its contributors may be used to endorse or promote products
//      derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
// THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef __SCANNER_H__
#define __SCANNER_H__

#include <cstdlib>

#include "cpp/enums/Token.hh"
//#include <string>

struct ParserState
{
    char *string;
    int number;
    double decimal;
    bool boolean;
    Token::Type token{Token::NoToken};
    unsigned int tokenLine;
    unsigned int tokenLinePosition;

    ParserState()
    {
        string = nullptr;
    }
    ~ParserState()
    {
        if (string != nullptr)
            std::free(string);
    }
};

class Scanner
{
  public:
    Scanner(const char *data, int length = -1);
    ~Scanner();

    void SetString(char **ptr, const char *src, unsigned int length);
    void CheckForWhitespace();
    bool CheckToken(Token::Type token);
    bool CheckInteger();
    bool CheckFloat();
    void MustGetInteger();
    void MustGetFloat();
    void ExpandState();
    int GetLine() const
    {
        return tokenLine;
    }
    int GetLinePos() const
    {
        return tokenLinePosition;
    }
    bool GetNextToken(bool expandState = true);
    void MustGetToken(Token::Type token);
    void MustGetIdentifier(const char *ident);
    bool TokensLeft() const;
    void Error(Token::Type token);
    void Error(const char *mustget);
    void ErrorF(const char *msg, ...);
    void Unget()
    {
        needNext = true;
    }
    static void SetErrorCallback(void (*cb)(const char *, ...))
    {
        error = cb;
    }

    static void Unescape(char *str);

    static const char *const TokenNames[Token::NumSpecialTokens.value()];

    char *string;
    int number;
    double decimal;
    bool boolean;
    Token::Type token{Token::NoToken};

  protected:
    Scanner()
    {
        data = nullptr;
        string = nullptr;
        nextState.string = nullptr;
    }

    void IncrementLine();
    void SaveState(Scanner &saved);
    void RestoreState(Scanner &savd);
    bool ScanInteger();
    bool ScanFloat();

  private:
    ParserState nextState;

    char *data;
    unsigned int length;

    unsigned int line;
    unsigned int lineStart;
    unsigned int logicalPosition;
    unsigned int tokenLine;
    unsigned int tokenLinePosition;
    unsigned int scanPos;

    bool needNext; // If checkToken returns false this will be false.

    static void (*error)(const char *message, ...);
};

#endif /* __SCANNER_H__ */
