﻿#pragma once

#include <string>
#include <vector>

#include "Declarations.h"


/*
 * [The "BSD license"]
 * Copyright (c) 2013 Terence Parr
 * Copyright (c) 2013 Sam Harwell
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

namespace org {
    namespace antlr {
        namespace v4 {
            namespace runtime {
                namespace tree {
                    namespace pattern {
                        /// <summary>
                        /// A pattern like {@code <ID> = <expr>;} converted to a <seealso cref="ParseTree"/> by
                        /// <seealso cref="ParseTreePatternMatcher#compile(String, int)"/>.
                        /// </summary>
                        class ParseTreePattern {
                            /// <summary>
                            /// This is the backing field for <seealso cref="#getPatternRuleIndex()"/>.
                            /// </summary>
                        private:
                            const int patternRuleIndex;

                            /// <summary>
                            /// This is the backing field for <seealso cref="#getPattern()"/>.
                            /// </summary>
                            const std::wstring pattern;

                            /// <summary>
                            /// This is the backing field for <seealso cref="#getPatternTree()"/>.
                            /// </summary>
                            ParseTree *const patternTree;

                            /// <summary>
                            /// This is the backing field for <seealso cref="#getMatcher()"/>.
                            /// </summary>
                            ParseTreePatternMatcher *const matcher;

                            /// <summary>
                            /// Construct a new instance of the <seealso cref="ParseTreePattern"/> class.
                            /// </summary>
                            /// <param name="matcher"> The <seealso cref="ParseTreePatternMatcher"/> which created this
                            /// tree pattern. </param>
                            /// <param name="pattern"> The tree pattern in concrete syntax form. </param>
                            /// <param name="patternRuleIndex"> The parser rule which serves as the root of the
                            /// tree pattern. </param>
                            /// <param name="patternTree"> The tree pattern in <seealso cref="ParseTree"/> form. </param>
                        public:
                            ParseTreePattern(ParseTreePatternMatcher *matcher, const std::wstring &pattern, int patternRuleIndex, ParseTree *patternTree);

                            /// <summary>
                            /// Match a specific parse tree against this tree pattern.
                            /// </summary>
                            /// <param name="tree"> The parse tree to match against this tree pattern. </param>
                            /// <returns> A <seealso cref="ParseTreeMatch"/> object describing the result of the
                            /// match operation. The <seealso cref="ParseTreeMatch#succeeded()"/> method can be
                            /// used to determine whether or not the match was successful. </returns>
                            virtual ParseTreeMatch *match(ParseTree *tree);

                            /// <summary>
                            /// Determine whether or not a parse tree matches this tree pattern.
                            /// </summary>
                            /// <param name="tree"> The parse tree to match against this tree pattern. </param>
                            /// <returns> {@code true} if {@code tree} is a match for the current tree
                            /// pattern; otherwise, {@code false}. </returns>
                            virtual bool matches(ParseTree *tree);

// TODO:  Come back to this after the base runtime works.
#if 0
                            /// <summary>
                            /// Find all nodes using XPath and then try to match those subtrees against
                            /// this tree pattern.
                            /// </summary>
                            /// <param name="tree"> The <seealso cref="ParseTree"/> to match against this pattern. </param>
                            /// <param name="xpath"> An expression matching the nodes
                            /// </param>
                            /// <returns> A collection of <seealso cref="ParseTreeMatch"/> objects describing the
                            /// successful matches. Unsuccessful matches are omitted from the result,
                            /// regardless of the reason for the failure. </returns>
                            virtual std::vector<ParseTreeMatch*> findAll(ParseTree *tree, const std::wstring &xpath);
#endif
                            
                            /// <summary>
                            /// Get the <seealso cref="ParseTreePatternMatcher"/> which created this tree pattern.
                            /// </summary>
                            /// <returns> The <seealso cref="ParseTreePatternMatcher"/> which created this tree
                            /// pattern. </returns>
                            virtual ParseTreePatternMatcher *getMatcher();

                            /// <summary>
                            /// Get the tree pattern in concrete syntax form.
                            /// </summary>
                            /// <returns> The tree pattern in concrete syntax form. </returns>
                            virtual std::wstring getPattern();

                            /// <summary>
                            /// Get the parser rule which serves as the outermost rule for the tree
                            /// pattern.
                            /// </summary>
                            /// <returns> The parser rule which serves as the outermost rule for the tree
                            /// pattern. </returns>
                            virtual int getPatternRuleIndex();

                            /// <summary>
                            /// Get the tree pattern as a <seealso cref="ParseTree"/>. The rule and token tags from
                            /// the pattern are present in the parse tree as terminal nodes with a symbol
                            /// of type <seealso cref="RuleTagToken"/> or <seealso cref="TokenTagToken"/>.
                            /// </summary>
                            /// <returns> The tree pattern as a <seealso cref="ParseTree"/>. </returns>
                            virtual ParseTree *getPatternTree();
                        };

                    }
                }
            }
        }
    }
}
