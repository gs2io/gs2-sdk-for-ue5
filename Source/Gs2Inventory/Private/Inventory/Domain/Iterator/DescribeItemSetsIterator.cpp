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

#include "Inventory/Domain/Iterator/DescribeItemSetsIterator.h"
#include "Inventory/Domain/Model/ItemSet.h"
#include "Inventory/Domain/Model/Inventory.h"

namespace Gs2::Inventory::Domain::Iterator
{

    FDescribeItemSetsIterator::FDescribeItemSetsIterator(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Inventory::FGs2InventoryRestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> InventoryName,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        Client(Client),
        NamespaceName(NamespaceName),
        InventoryName(InventoryName),
        AccessToken(AccessToken)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDescribeItemSetsIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::Inventory::Model::FItemSet>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FDescribeItemSetsIterator::FIterator::FIterator(
        const TSharedRef<FDescribeItemSetsIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        PageToken(TOptional<FString>()),
        FetchSize(TOptional<int32>())
    {
    }

    FDescribeItemSetsIterator::FIterator& FDescribeItemSetsIterator::FIterator::operator++()
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
            const auto ListParentKey = Gs2::Inventory::Domain::Model::FInventoryDomain::CreateCacheParentKey(
            Self->NamespaceName,
            Self->UserId(),
            Self->InventoryName,
            "ItemSet"
        );
            if (Self->Cache->IsListCached(
                Gs2::Inventory::Model::FItemSet::TypeName,
                ListParentKey
            )) {
                Range = MakeShared<TArray<Gs2::Inventory::Model::FItemSetPtr>>();
                *Range = Self->Cache->List<Gs2::Inventory::Model::FItemSet>(
                    ListParentKey
                );
                RangeIteratorOpt = Range->CreateIterator();
                PageToken = TOptional<FString>();
                bLast = true;
                bEnd = static_cast<bool>(*RangeIteratorOpt);
                return *this;
            }
            const auto Future = Self->Client->DescribeItemSets(
                MakeShared<Gs2::Inventory::Request::FDescribeItemSetsRequest>()
                    ->WithNamespaceName(Self->NamespaceName)
                    ->WithInventoryName(Self->InventoryName)
                    ->WithAccessToken(Self->AccessToken == nullptr ? TOptional<FString>() : Self->AccessToken->GetToken())
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
                    Gs2::Inventory::Model::FItemSet::TypeName,
                    ListParentKey,
                    Gs2::Inventory::Domain::Model::FItemSetDomain::CreateCacheKey(
                        Item->GetItemName(),
                        Item->GetName()
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

    FDescribeItemSetsIterator::FIterator FDescribeItemSetsIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FDescribeItemSetsIterator::FIterator FDescribeItemSetsIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FDescribeItemSetsIterator::FIterator FDescribeItemSetsIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

