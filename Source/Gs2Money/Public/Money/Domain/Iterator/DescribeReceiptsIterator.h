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
#include "Money/Gs2Money.h"

namespace Gs2::Money::Domain::Iterator
{

    class FDescribeReceiptsIteratorLoadTask;

    class GS2MONEY_API FDescribeReceiptsIterator :
        public Gs2::Core::Domain::Model::TGs2Iterator<Gs2::Money::Model::FReceipt, FDescribeReceiptsIteratorLoadTask>
    {
        const Core::Domain::FCacheDatabasePtr Cache;
        const Gs2::Money::FGs2MoneyRestClientPtr Client;

        friend FDescribeReceiptsIteratorLoadTask;
        virtual TSharedPtr<FAsyncTask<FDescribeReceiptsIteratorLoadTask>> Load() override;

public:
        const TOptional<FString> NamespaceName;
        const TOptional<FString> UserId;
        const TOptional<int32> Slot;
        const TOptional<int64> Begin;
        const TOptional<int64> End;
        TOptional<FString> PageToken;
        TOptional<int32> FetchSize;

        FDescribeReceiptsIterator(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Money::FGs2MoneyRestClientPtr Client,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<int32> Slot,
            const TOptional<int64> Begin,
            const TOptional<int64> End
        );

        class GS2MONEY_API IteratorImpl
        {
            friend FDescribeReceiptsIterator;

            TSharedPtr<FAsyncTask<Gs2::Money::Domain::Iterator::FDescribeReceiptsIterator::FNextTask>> Task;
            Gs2::Money::Model::FReceiptPtr Current;

        public:
            explicit IteratorImpl(
                const TSharedPtr<FAsyncTask<Gs2::Money::Domain::Iterator::FDescribeReceiptsIterator::FNextTask>> Task
            ): Task(Task)
            {

            }
            const Gs2::Money::Model::FReceiptPtr& operator*() const;
            Gs2::Money::Model::FReceiptPtr operator->();
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
    typedef TSharedPtr<FDescribeReceiptsIterator> FDescribeReceiptsIteratorPtr;

    class FDescribeReceiptsIteratorLoadTask :
        public Gs2::Core::Util::TGs2Future<TArray<Gs2::Money::Model::FReceiptPtr>>,
        public TSharedFromThis<FDescribeReceiptsIteratorLoadTask>
    {
        TSharedPtr<FDescribeReceiptsIterator> Self;

    public:
        explicit FDescribeReceiptsIteratorLoadTask(
            TSharedPtr<FDescribeReceiptsIterator> Self
        ): Self(Self)
        {

        }

        virtual Gs2::Core::Model::FGs2ErrorPtr Action(
            TSharedPtr<TSharedPtr<TArray<Gs2::Money::Model::FReceiptPtr>>> Result
        ) override;
    };
}
