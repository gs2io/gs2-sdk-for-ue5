
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

#include "Core/Domain/Gs2.h"

#include "Inventory/Model/Cache/ReferenceOf.h"
#include "Inventory/Model/Cache/ItemSet.h"
#include "Inventory/Model/Cache/ItemModel.h"
#include "Inventory/Model/Cache/Inventory.h"

namespace Gs2::Inventory::Domain::Iterator
{

    FDescribeReferenceOfIterator::FDescribeReferenceOfIterator(
        const TSharedPtr<Core::Domain::FGs2> Gs2,
        const Gs2::Inventory::FGs2InventoryRestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> InventoryName,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken,
        const TOptional<FString> ItemName,
        const TOptional<FString> ItemSetName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(Client),
        NamespaceName(NamespaceName),
        InventoryName(InventoryName),
        AccessToken(AccessToken),
        ItemName(ItemName),
        ItemSetName(ItemSetName)
    {
    }

    FDescribeReferenceOfIterator::FDescribeReferenceOfIterator(
        const FDescribeReferenceOfIterator& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        InventoryName(From.InventoryName),
        AccessToken(From.AccessToken),
        ItemName(From.ItemName),
        ItemSetName(From.ItemSetName)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDescribeReferenceOfIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<FString>> Result)
    {
        ++Iterator;
        if (!Iterator.IsCurrentValid()) { *Result = nullptr; return Iterator.Error(); }
        *Result = MakeShared<FString>(Iterator->Current());
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

        if (RangeIteratorOpt && *RangeIteratorOpt) ++*RangeIteratorOpt;

        // Keep the previous page alive until its iterator has been replaced.
        const auto PreviousRange = Range;
        if (!RangeIteratorOpt || (!*RangeIteratorOpt && !bLast))
        {
            const auto ListParentKey = Gs2::Inventory::Model::Cache::FReferenceOfCache::CreateCacheParentKey(

                Self->NamespaceName,
                Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>(),
                Self->InventoryName,
                Self->ItemName,
                Self->ItemSetName,
                Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>()
            );
            if (!RangeIteratorOpt)
            {
                auto CachedValues = Self->Gs2->Cache->TryGetList<Gs2::Inventory::Model::FReferenceOf>(ListParentKey);
                if (CachedValues)
                {
                    Range = MakeShared<TArray<FString>>();
                    for (const auto& Item : *CachedValues)
                    {
                        if (Item.IsValid() && Item->GetName().IsSet()) Range->Add(Item->GetName().Get(FString()));
                    }
                }

                if (Range)
                {
                    bLast = true;
                    RangeIteratorOpt = Range->CreateIterator();
                    bEnd = !static_cast<bool>(*RangeIteratorOpt) && bLast;
                    return *this;
                }
            }
            const auto Future = Self->Client->DescribeReferenceOf(
                MakeShared<Gs2::Inventory::Request::FDescribeReferenceOfRequest>()
                    ->WithContextStack(Self->Gs2->DefaultContextStack)
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
            const auto ResultModel = R;
            Future->EnsureCompletion();
            Range = R->GetItems().IsValid() ? R->GetItems() : MakeShared<TArray<FString>>();
            for (const auto& Item : *Range)
            {
                Gs2::Inventory::Model::Cache::FReferenceOfCache::Put(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>(),
                    Self->InventoryName,
                    Self->ItemName,
                    Self->ItemSetName,
                    Item,
                    Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>(),
                    MakeShared<Gs2::Inventory::Model::FReferenceOf>()
                        ->WithName(Item)
                );
            }
            if (Range)
            {
            }
            RangeIteratorOpt = Range->CreateIterator();
            bLast = true;
            if (bLast) {
                Self->Gs2->Cache->SetListCached(
                    Gs2::Inventory::Model::FReferenceOf::TypeName,
                    ListParentKey
                );
            }
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

