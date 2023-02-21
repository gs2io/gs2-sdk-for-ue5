/*
 * Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

// ReSharper disable CppUnusedIncludeDirective

#pragma once

#include "Core/Domain/Gs2Core.h"
#include "Auth/Gs2Auth.h"
#include "Script/Gs2Script.h"

namespace Gs2::Script::Domain::Iterator
{

    class FDescribeScriptsIteratorLoadTask;

    class GS2SCRIPT_API FDescribeScriptsIterator :
        public Gs2::Core::Domain::Model::TGs2Iterator<Gs2::Script::Model::FScript, FDescribeScriptsIteratorLoadTask>
    {
        const Core::Domain::FCacheDatabasePtr Cache;
        const Gs2::Script::FGs2ScriptRestClientPtr Client;

        friend FDescribeScriptsIteratorLoadTask;
        virtual TSharedPtr<FAsyncTask<FDescribeScriptsIteratorLoadTask>> Load() override;

public:
        const TOptional<FString> NamespaceName;
        TOptional<FString> PageToken;
        TOptional<int32> FetchSize;

        FDescribeScriptsIterator(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Script::FGs2ScriptRestClientPtr Client,
            const TOptional<FString> NamespaceName
        );

        class GS2SCRIPT_API IteratorImpl
        {
            friend FDescribeScriptsIterator;

            TSharedPtr<FAsyncTask<Gs2::Script::Domain::Iterator::FDescribeScriptsIterator::FNextTask>> Task;
            Gs2::Script::Model::FScriptPtr Current;

        public:
            explicit IteratorImpl(
                const TSharedPtr<FAsyncTask<Gs2::Script::Domain::Iterator::FDescribeScriptsIterator::FNextTask>> Task
            ): Task(Task)
            {

            }
            const Gs2::Script::Model::FScriptPtr& operator*() const;
            Gs2::Script::Model::FScriptPtr operator->();
            IteratorImpl& operator++();

            friend bool operator== (const IteratorImpl& a, const IteratorImpl& b)
            {
                if (a.Task == nullptr && b.Task == nullptr)
                {
                    return true;
                }
                if (a.Task == nullptr)
                {
                    return b.Current == nullptr;
                }
                if (b.Task == nullptr)
                {
                    return a.Current == nullptr;
                }
                return a.Current == b.Current;
            };
            friend bool operator!= (const IteratorImpl& a, const IteratorImpl& b)
            {
                return !operator==(a, b);
            };
        };

        IteratorImpl begin();
        IteratorImpl end();
    };
    typedef TSharedPtr<FDescribeScriptsIterator> FDescribeScriptsIteratorPtr;

    class FDescribeScriptsIteratorLoadTask :
        public Gs2::Core::Util::TGs2Future<TArray<Gs2::Script::Model::FScriptPtr>>,
        public TSharedFromThis<FDescribeScriptsIteratorLoadTask>
    {
        TSharedPtr<FDescribeScriptsIterator> Self;

    public:
        explicit FDescribeScriptsIteratorLoadTask(
            TSharedPtr<FDescribeScriptsIterator> Self
        ): Self(Self)
        {

        }

        virtual Gs2::Core::Model::FGs2ErrorPtr Action(
            TSharedPtr<TSharedPtr<TArray<Gs2::Script::Model::FScriptPtr>>> Result
        ) override;
    };
}
