﻿#pragma once

#include "Lexer.h"
#include "Declarations.h"
#include <string>
#include <vector>

/*
 * [The "BSD license"]
 *  Copyright (c) 2013 Terence Parr
 *  Copyright (c) 2013 Dan McLaughlin
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *  3. The name of the author may not be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 *  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 *  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 *  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 *  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

namespace org {
    namespace antlr {
        namespace v4 {
            namespace runtime {
                class LexerInterpreter : public Lexer {
                protected:
                    const std::wstring grammarFileName;
                    atn::ATN *const atn;


                    std::vector<std::wstring> _tokenNames;

                    std::vector<std::wstring> _ruleNames;

                    std::vector<std::wstring> _modeNames;

                    std::vector<dfa::DFA*> _decisionToDFA;
                    
                    atn::PredictionContextCache *const _sharedContextCache;

                public:
                    LexerInterpreter(const std::wstring &grammarFileName, std::vector<std::wstring> *tokenNames, std::vector<std::wstring> *ruleNames, std::vector<std::wstring> *modeNames, atn::ATN *atn, CharStream *input);

                    virtual atn::ATN *getATN() override;

                    virtual std::wstring getGrammarFileName() override;

                    virtual const std::vector<std::wstring>& getTokenNames() override;

                    virtual const std::vector<std::wstring>& getRuleNames() override;

                    virtual const std::vector<std::wstring>& getModeNames() override;
                };

            }
        }
    }
}
