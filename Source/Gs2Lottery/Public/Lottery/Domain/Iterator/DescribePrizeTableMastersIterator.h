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
#include "Lottery/Gs2Lottery.h"

namespace Gs2::Lottery::Domain::Iterator
{

    class FDescribePrizeTableMastersIteratorLoadTask;

    class GS2LOTTERY_API FDescribePrizeTableMastersIterator :
        public Gs2::Core::Domain::Model::TGs2Iterator<Gs2::Lottery::Model::FPrizeTableMaster, FDescribePrizeTableMastersIteratorLoadTask>
    {
        const Core::Domain::FCacheDatabasePtr Cache;
        const Gs2::Lottery::FGs2LotteryRestClientPtr Client;

        friend FDescribePrizeTableMastersIteratorLoadTask;
        virtual TSharedPtr<FAsyncTask<FDescribePrizeTableMastersIteratorLoadTask>> Load() override;

public:
        const TOptional<FString> NamespaceName;
        TOptional<FString> PageToken;
        TOptional<int32> FetchSize;

        FDescribePrizeTableMastersIterator(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Lottery::FGs2LotteryRestClientPtr Client,
            const TOptional<FString> NamespaceName
        );

        class GS2LOTTERY_API IteratorImpl
        {
            friend FDescribePrizeTableMastersIterator;

            TSharedPtr<FAsyncTask<Gs2::Lottery::Domain::Iterator::FDescribePrizeTableMastersIterator::FNextTask>> Task;
            Gs2::Lottery::Model::FPrizeTableMasterPtr Current;

        public:
            explicit IteratorImpl(
                const TSharedPtr<FAsyncTask<Gs2::Lottery::Domain::Iterator::FDescribePrizeTableMastersIterator::FNextTask>> Task
            ): Task(Task)
            {

            }
            const Gs2::Lottery::Model::FPrizeTableMasterPtr& operator*() const;
            Gs2::Lottery::Model::FPrizeTableMasterPtr operator->();
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
    typedef TSharedPtr<FDescribePrizeTableMastersIterator> FDescribePrizeTableMastersIteratorPtr;

    class FDescribePrizeTableMastersIteratorLoadTask :
        public Gs2::Core::Util::TGs2Future<TArray<Gs2::Lottery::Model::FPrizeTableMasterPtr>>,
        public TSharedFromThis<FDescribePrizeTableMastersIteratorLoadTask>
    {
        TSharedPtr<FDescribePrizeTableMastersIterator> Self;

    public:
        explicit FDescribePrizeTableMastersIteratorLoadTask(
            TSharedPtr<FDescribePrizeTableMastersIterator> Self
        ): Self(Self)
        {

        }

        virtual Gs2::Core::Model::FGs2ErrorPtr Action(
            TSharedPtr<TSharedPtr<TArray<Gs2::Lottery::Model::FPrizeTableMasterPtr>>> Result
        ) override;
    };
}
