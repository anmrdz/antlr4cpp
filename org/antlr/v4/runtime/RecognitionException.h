﻿#pragma once

#include "Recognizer.h"
#include "Declarations.h"
#include "Exceptions.h"

#include <string>
#include <stdexcept>


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

                class RuntimeException : public ANTLRException {
                public:
                    RuntimeException(const std::wstring msg);
                    RuntimeException();
                };
                
                /// <summary>
                /// The root of the ANTLR exception hierarchy. In general, ANTLR tracks just
                ///  3 kinds of errors: prediction errors, failed predicate errors, and
                ///  mismatched input errors. In each case, the parser knows where it is
                ///  in the input, where it is in the ATN, the rule invocation stack,
                ///  and what kind of problem occurred.
                /// </summary>
                class RecognitionException : public RuntimeException {
                    /// <summary>
                    /// The <seealso cref="Recognizer"/> where this exception originated. </summary>
                private:
                    Recognizer<void*, void*> *const recognizer;

                    RuleContext *const ctx;

                    IntStream *const input;

                    /// <summary>
                    /// The current <seealso cref="Token"/> when an error occurred. Since not all streams
                    /// support accessing symbols by index, we have to track the <seealso cref="Token"/>
                    /// instance itself.
                    /// </summary>
                    Token *offendingToken;

                    int offendingState;

                public:
                    template<typename T1, typename T2>
                    RecognitionException(Recognizer<T1, T2> *recognizer, IntStream *input, ParserRuleContext *ctx);

                    template<typename T1, typename T2>
                    RecognitionException(const std::wstring &message, Recognizer<T1, T2> *recognizer, IntStream *input, ParserRuleContext *ctx);
                    
                    RecognitionException() : ctx(nullptr), recognizer(nullptr), input(nullptr) {}
                    
                    /// <summary>
                    /// Get the ATN state number the parser was in at the time the error
                    /// occurred. For <seealso cref="NoViableAltException"/> and
                    /// <seealso cref="LexerNoViableAltException"/> exceptions, this is the
                    /// <seealso cref="DecisionState"/> number. For others, it is the state whose outgoing
                    /// edge we couldn't match.
                    /// <p/>
                    /// If the state number is not known, this method returns -1.
                    /// </summary>
                    virtual int getOffendingState();

                protected:
                    void setOffendingState(int offendingState);

                    /// <summary>
                    /// Gets the set of input symbols which could potentially follow the
                    /// previously matched symbol at the time this exception was thrown.
                    /// <p/>
                    /// If the set of expected tokens is not known and could not be computed,
                    /// this method returns {@code null}.
                    /// </summary>
                    /// <returns> The set of token types that could potentially follow the current
                    /// state in the ATN, or {@code null} if the information is not available. </returns>
                public:
                    virtual misc::IntervalSet *getExpectedTokens();

                    /// <summary>
                    /// Gets the <seealso cref="RuleContext"/> at the time this exception was thrown.
                    /// <p/>
                    /// If the context is not available, this method returns {@code null}.
                    /// </summary>
                    /// <returns> The <seealso cref="RuleContext"/> at the time this exception was thrown.
                    /// If the context is not available, this method returns {@code null}. </returns>
                    virtual RuleContext *getCtx();

                    /// <summary>
                    /// Gets the input stream which is the symbol source for the recognizer where
                    /// this exception was thrown.
                    /// <p/>
                    /// If the input stream is not available, this method returns {@code null}.
                    /// </summary>
                    /// <returns> The input stream which is the symbol source for the recognizer
                    /// where this exception was thrown, or {@code null} if the stream is not
                    /// available. </returns>
                    virtual IntStream *getInputStream();

                    virtual Token *getOffendingToken();

                protected:
                    void setOffendingToken(Token *offendingToken);

                    /// <summary>
                    /// Gets the <seealso cref="Recognizer"/> where this exception occurred.
                    /// <p/>
                    /// If the recognizer is not available, this method returns {@code null}.
                    /// </summary>
                    /// <returns> The recognizer where this exception occurred, or {@code null} if
                    /// the recognizer is not available. </returns>
                public:
                    virtual Recognizer<void*, void*> *getRecognizer();

                private:
                    void InitializeInstanceFields();
                };

                // Recognition exceptions
                
                class ParseCancellationException : public RecognitionException {
                public:
                    ParseCancellationException(const std::wstring msg);
                    ParseCancellationException(RecognitionException*);
                    ParseCancellationException();
                };
                
                class EmptyStackException : public RecognitionException {
                public:
                    EmptyStackException(const std::wstring msg);
                    EmptyStackException();
                };
                
            }
        }
    }
}
