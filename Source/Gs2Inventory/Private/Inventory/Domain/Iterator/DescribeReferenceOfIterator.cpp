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

#include "Inventory/Domain/Iterator/DescribeReferenceOfIterator.h"
#include "Inventory/Domain/Model/ReferenceOf.h"
#include "Inventory/Domain/Model/ItemSet.h"

namespace Gs2::Inventory::Domain::Iterator
{

    FDescribeReferenceOfIterator::FDescribeReferenceOfIterator(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Inventory::FGs2InventoryRestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> InventoryName,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken,
        const TOptional<FString> ItemName,
        const TOptional<FString> ItemSetName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        Client(Client),
        NamespaceName(NamespaceName),
        InventoryName(InventoryName),
        AccessToken(AccessToken),
        ItemName(ItemName),
        ItemSetName(ItemSetName)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDescribeReferenceOfIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Inventory::Model::FReferenceOfEntry>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FDescribeReferenceOfIterator::FIterator::FIterator(
        const TSharedRef<FDescribeReferenceOfIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        FetchSize(TOptional<int32>())
    {
    }

    FDescribeReferenceOfIterator::FIterator& FDescribeReferenceOfIterator::FIterator::operator++()
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
            const auto ListParentKey = "inventory:String";
            if (Self->Cache->IsListCached(
                Gs2::Inventory::Model::FReferenceOfEntry::TypeName,
                ListParentKey
            )) {
                Range = MakeShared<TArray<Gs2::Inventory::Model::FReferenceOfEntryPtr>>();
                *Range = Self->Cache->List<Gs2::Inventory::Model::FReferenceOfEntry>(
                    ListParentKey
                );
                RangeIteratorOpt = Range->CreateIterator();
                bLast = true;
                bEnd = static_cast<bool>(*RangeIteratorOpt);
                return *this;
            }
            const auto Future = Self->Client->DescribeReferenceOf(
                MakeShared<Gs2::Inventory::Request::FDescribeReferenceOfRequest>()
                    ->WithNamespaceName(Self->NamespaceName)
                    ->WithInventoryName(Self->InventoryName)
                    ->WithAccessToken(Self->AccessToken == nullptr ? TOptional<FString>() : Self->AccessToken->GetToken())
                    ->WithItemName(Self->ItemName)
                    ->WithItemSetName(Self->ItemSetName)
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
            if (!Range.IsValid())
            {
                Range = MakeShared<TArray<Inventory::Model::FReferenceOfEntryPtr>>();
            }
            for (auto Item : *R->GetItems())
            {
                Range->Add(MakeShared<Inventory::Model::FReferenceOfEntry>(Item));
            }
            for (auto Item : *R->GetItems())
            {
                Self->Cache->Put(
                    Gs2::Inventory::Model::FReferenceOfEntry::TypeName,
                    ListParentKey,
                    Gs2::Inventory::Domain::Model::FReferenceOfDomain::CreateCacheKey(
                        Item
                    ),
                    MakeShared<FString>(Item),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            RangeIteratorOpt = Range->CreateIterator();
            bLast = true;
        }

        bEnd = bLast && !*RangeIteratorOpt;
        return *this;
    }

    FDescribeReferenceOfIterator::FIterator FDescribeReferenceOfIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FDescribeReferenceOfIterator::FIterator FDescribeReferenceOfIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FDescribeReferenceOfIterator::FIterator FDescribeReferenceOfIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

