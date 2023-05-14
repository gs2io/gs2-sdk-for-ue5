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

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

// ReSharper disable CppUnusedIncludeDirective

#include "Money/Domain/Iterator/DescribeWalletsByUserIdIterator.h"
#include "Money/Domain/Model/Wallet.h"
#include "Money/Domain/Model/User.h"

namespace Gs2::Money::Domain::Iterator
{

    FDescribeWalletsByUserIdIterator::FDescribeWalletsByUserIdIterator(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Money::FGs2MoneyRestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        Client(Client),
        NamespaceName(NamespaceName),
        UserId(UserId)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDescribeWalletsByUserIdIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::Money::Model::FWallet>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FDescribeWalletsByUserIdIterator::FIterator::FIterator(
        const TSharedRef<FDescribeWalletsByUserIdIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        PageToken(TOptional<FString>()),
        FetchSize(TOptional<int32>())
    {
    }

    FDescribeWalletsByUserIdIterator::FIterator& FDescribeWalletsByUserIdIterator::FIterator::operator++()
    {
        

        if (bEnd) return *this;

        if (ErrorValue && bLast)
        {
            bEnd = true;
            return *this;
        }

        if (RangeIteratorOpt) ++*RangeIteratorOpt;

        if (!RangeIteratorOpt || (!*RangeIteratorOpt && !bLast))
        {
            const auto ListParentKey = Gs2::Money::Domain::Model::FUserDomain::CreateCacheParentKey(
            Self->NamespaceName,
            Self->UserId,
            "Wallet"
        );
            if (Self->Cache->IsListCached(
                Gs2::Money::Model::FWallet::TypeName,
                ListParentKey
            )) {
                Range = MakeShared<TArray<Gs2::Money::Model::FWalletPtr>>();
                *Range = Self->Cache->List<Gs2::Money::Model::FWallet>(
                    ListParentKey
                );
                RangeIteratorOpt = Range->CreateIterator();
                PageToken = TOptional<FString>();
                bLast = true;
                bEnd = static_cast<bool>(*RangeIteratorOpt);
                return *this;
            }
            const auto Future = Self->Client->DescribeWalletsByUserId(
                MakeShared<Gs2::Money::Request::FDescribeWalletsByUserIdRequest>()
                    ->WithNamespaceName(Self->NamespaceName)
                    ->WithUserId(Self->UserId)
                    ->WithPageToken(PageToken)
                    ->WithLimit(FetchSize)
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                ErrorValue = Future->GetTask().Error();
                bLast = true;
                return *this;
            }
            else
            {
                ErrorValue = nullptr;
            }
            const auto R = Future->GetTask().Result();
            Future->EnsureCompletion();
            Range = R->GetItems();
            for (auto Item : *R->GetItems())
            {
                Self->Cache->Put(
                    Gs2::Money::Model::FWallet::TypeName,
                    ListParentKey,
                    Gs2::Money::Domain::Model::FWalletDomain::CreateCacheKey(
                        FString::FromInt(*Item->GetSlot())
                    ),
                    Item,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            RangeIteratorOpt = Range->CreateIterator();
            PageToken = R->GetNextPageToken();
            bLast = !PageToken.IsSet();
        }

        bEnd = bLast && !*RangeIteratorOpt;
        return *this;
    }

    FDescribeWalletsByUserIdIterator::FIterator FDescribeWalletsByUserIdIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FDescribeWalletsByUserIdIterator::FIterator FDescribeWalletsByUserIdIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FDescribeWalletsByUserIdIterator::FIterator FDescribeWalletsByUserIdIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

