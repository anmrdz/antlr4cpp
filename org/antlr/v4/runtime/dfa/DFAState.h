﻿#pragma once

#include <string>
#include <set>
#include <vector>

#include "Declarations.h"

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
                namespace dfa {
                    /// <summary>
                    /// A DFA state represents a set of possible ATN configurations.
                    ///  As Aho, Sethi, Ullman p. 117 says "The DFA uses its state
                    ///  to keep track of all possible states the ATN can be in after
                    ///  reading each input symbol.  That is to say, after reading
                    ///  input a1a2..an, the DFA is in a state that represents the
                    ///  subset T of the states of the ATN that are reachable from the
                    ///  ATN's start state along some path labeled a1a2..an."
                    ///  In conventional NFA->DFA conversion, therefore, the subset T
                    ///  would be a bitset representing the set of states the
                    ///  ATN could be in.  We need to track the alt predicted by each
                    ///  state as well, however.  More importantly, we need to maintain
                    ///  a stack of states, tracking the closure operations as they
                    ///  jump from rule to rule, emulating rule invocations (method calls).
                    ///  I have to add a stack to simulate the proper lookahead sequences for
                    ///  the underlying LL grammar from which the ATN was derived.
                    /// <p/>
                    ///  I use a set of ATNConfig objects not simple states.  An ATNConfig
                    ///  is both a state (ala normal conversion) and a RuleContext describing
                    ///  the chain of rules (if any) followed to arrive at that state.
                    /// <p/>
                    ///  A DFA state may have multiple references to a particular state,
                    ///  but with different ATN contexts (with same or different alts)
                    ///  meaning that state was reached via a different set of rule invocations.
                    /// </summary>
                    class DFAState {
                    public:
                        class PredPrediction {
                        public:
                            atn::SemanticContext *pred; // never null; at least SemanticContext.NONE
                            int alt;
                            PredPrediction(atn::SemanticContext *pred, int alt);
                            virtual std::wstring toString();

                        private:
                            void InitializeInstanceFields();
                        };

                    public:
                        int stateNumber;

                        atn::ATNConfigSet *configs;

                        /// <summary>
                        /// {@code edges[symbol]} points to target of symbol. Shift up by 1 so (-1)
                        ///  <seealso cref="Token#EOF"/> maps to {@code edges[0]}.
                        /// </summary>
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
//ORIGINAL LINE: @Nullable public DFAState[] edges;
                        std::vector<DFAState*> edges;

                        bool isAcceptState;

                        /// <summary>
                        /// if accept state, what ttype do we match or alt do we predict?
                        ///  This is set to <seealso cref="ATN#INVALID_ALT_NUMBER"/> when <seealso cref="#predicates"/>{@code !=null} or
                        ///  <seealso cref="#requiresFullContext"/>.
                        /// </summary>
                        int prediction;

                        int lexerRuleIndex; // if accept, exec action in what rule?
                        int lexerActionIndex; // if accept, exec what action?

                        /// <summary>
                        /// Indicates that this state was created during SLL prediction that
                        /// discovered a conflict between the configurations in the state. Future
                        /// <seealso cref="ParserATNSimulator#execATN"/> invocations immediately jumped doing
                        /// full context prediction if this field is true.
                        /// </summary>
                        bool requiresFullContext;

                        /// <summary>
                        /// During SLL parsing, this is a list of predicates associated with the
                        ///  ATN configurations of the DFA state. When we have predicates,
                        ///  <seealso cref="#requiresFullContext"/> is {@code false} since full context prediction evaluates predicates
                        ///  on-the-fly. If this is not null, then <seealso cref="#prediction"/> is
                        ///  <seealso cref="ATN#INVALID_ALT_NUMBER"/>.
                        /// <p/>
                        ///  We only use these for non-<seealso cref="#requiresFullContext"/> but conflicting states. That
                        ///  means we know from the context (it's $ or we don't dip into outer
                        ///  context) that it's an ambiguity not a conflict.
                        /// <p/>
                        ///  This list is computed by <seealso cref="ParserATNSimulator#predicateDFAState"/>.
                        /// </summary>
//JAVA TO C++ CONVERTER WARNING: Since the array size is not known in this declaration, Java to C++ Converter has converted this array to a pointer.  You will need to call 'delete[]' where appropriate:
//ORIGINAL LINE: @Nullable public PredPrediction[] predicates;
                        std::vector<PredPrediction *> predicates;

                        /// <summary>
                        /// Map a predicate to a predicted alternative. </summary>
                        DFAState();

                        DFAState(int stateNumber);

                        DFAState(atn::ATNConfigSet *configs);

                        /// <summary>
                        /// Get the set of all alts mentioned by all ATN configurations in this
                        ///  DFA state.
                        /// </summary>
                        virtual std::set<int> *getAltSet();

                        virtual int hashCode() ;

                        /// <summary>
                        /// Two <seealso cref="DFAState"/> instances are equal if their ATN configuration sets
                        /// are the same. This method is used to see if a state already exists.
                        /// <p/>
                        /// Because the number of alternatives and number of ATN configurations are
                        /// finite, there is a finite number of DFA states that can be processed.
                        /// This is necessary to show that the algorithm terminates.
                        /// <p/>
                        /// Cannot test the DFA state numbers here because in
                        /// <seealso cref="ParserATNSimulator#addDFAState"/> we need to know if any other state
                        /// exists that has this exact set of ATN configurations. The
                        /// <seealso cref="#stateNumber"/> is irrelevant.
                        /// </summary>
                        virtual bool equals(void *o);

                        virtual std::wstring toString();

                    private:
                        void InitializeInstanceFields();
                    };

                }
            }
        }
    }
}
