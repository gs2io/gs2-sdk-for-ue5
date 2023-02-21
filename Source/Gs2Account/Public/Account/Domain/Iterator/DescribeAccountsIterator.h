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
#include "Account/Gs2Account.h"

namespace Gs2::Account::Domain::Iterator
{

    class FDescribeAccountsIteratorLoadTask;

    class GS2ACCOUNT_API FDescribeAccountsIterator :
        public Gs2::Core::Domain::Model::TGs2Iterator<Gs2::Account::Model::FAccount, FDescribeAccountsIteratorLoadTask>
    {
        const Core::Domain::FCacheDatabasePtr Cache;
        const Gs2::Account::FGs2AccountRestClientPtr Client;

        friend FDescribeAccountsIteratorLoadTask;
        virtual TSharedPtr<FAsyncTask<FDescribeAccountsIteratorLoadTask>> Load() override;

public:
        const TOptional<FString> NamespaceName;
        TOptional<FString> PageToken;
        TOptional<int32> FetchSize;

        FDescribeAccountsIterator(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Account::FGs2AccountRestClientPtr Client,
            const TOptional<FString> NamespaceName
        );

        class GS2ACCOUNT_API IteratorImpl
        {
            friend FDescribeAccountsIterator;

            TSharedPtr<FAsyncTask<Gs2::Account::Domain::Iterator::FDescribeAccountsIterator::FNextTask>> Task;
            Gs2::Account::Model::FAccountPtr Current;

        public:
            explicit IteratorImpl(
                const TSharedPtr<FAsyncTask<Gs2::Account::Domain::Iterator::FDescribeAccountsIterator::FNextTask>> Task
            ): Task(Task)
            {

            }
            const Gs2::Account::Model::FAccountPtr& operator*() const;
            Gs2::Account::Model::FAccountPtr operator->();
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
    typedef TSharedPtr<FDescribeAccountsIterator> FDescribeAccountsIteratorPtr;

    class FDescribeAccountsIteratorLoadTask :
        public Gs2::Core::Util::TGs2Future<TArray<Gs2::Account::Model::FAccountPtr>>,
        public TSharedFromThis<FDescribeAccountsIteratorLoadTask>
    {
        TSharedPtr<FDescribeAccountsIterator> Self;

    public:
        explicit FDescribeAccountsIteratorLoadTask(
            TSharedPtr<FDescribeAccountsIterator> Self
        ): Self(Self)
        {

        }

        virtual Gs2::Core::Model::FGs2ErrorPtr Action(
            TSharedPtr<TSharedPtr<TArray<Gs2::Account::Model::FAccountPtr>>> Result
        ) override;
    };
}
