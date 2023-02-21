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
#include "Identifier/Gs2Identifier.h"

namespace Gs2::Identifier::Domain::Iterator
{

    class FDescribePasswordsIteratorLoadTask;

    class GS2IDENTIFIER_API FDescribePasswordsIterator :
        public Gs2::Core::Domain::Model::TGs2Iterator<Gs2::Identifier::Model::FPassword, FDescribePasswordsIteratorLoadTask>
    {
        const Core::Domain::FCacheDatabasePtr Cache;
        const Gs2::Identifier::FGs2IdentifierRestClientPtr Client;

        friend FDescribePasswordsIteratorLoadTask;
        virtual TSharedPtr<FAsyncTask<FDescribePasswordsIteratorLoadTask>> Load() override;

public:
        const TOptional<FString> UserName;
        TOptional<FString> PageToken;
        TOptional<int32> FetchSize;

        FDescribePasswordsIterator(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Identifier::FGs2IdentifierRestClientPtr Client,
            const TOptional<FString> UserName
        );

        class GS2IDENTIFIER_API IteratorImpl
        {
            friend FDescribePasswordsIterator;

            TSharedPtr<FAsyncTask<Gs2::Identifier::Domain::Iterator::FDescribePasswordsIterator::FNextTask>> Task;
            Gs2::Identifier::Model::FPasswordPtr Current;

        public:
            explicit IteratorImpl(
                const TSharedPtr<FAsyncTask<Gs2::Identifier::Domain::Iterator::FDescribePasswordsIterator::FNextTask>> Task
            ): Task(Task)
            {

            }
            const Gs2::Identifier::Model::FPasswordPtr& operator*() const;
            Gs2::Identifier::Model::FPasswordPtr operator->();
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
    typedef TSharedPtr<FDescribePasswordsIterator> FDescribePasswordsIteratorPtr;

    class FDescribePasswordsIteratorLoadTask :
        public Gs2::Core::Util::TGs2Future<TArray<Gs2::Identifier::Model::FPasswordPtr>>,
        public TSharedFromThis<FDescribePasswordsIteratorLoadTask>
    {
        TSharedPtr<FDescribePasswordsIterator> Self;

    public:
        explicit FDescribePasswordsIteratorLoadTask(
            TSharedPtr<FDescribePasswordsIterator> Self
        ): Self(Self)
        {

        }

        virtual Gs2::Core::Model::FGs2ErrorPtr Action(
            TSharedPtr<TSharedPtr<TArray<Gs2::Identifier::Model::FPasswordPtr>>> Result
        ) override;
    };
}
