
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

#include "Enchant/Domain/Iterator/DescribeRarityParameterModelMastersIterator.h"
#include "Enchant/Domain/Model/RarityParameterModelMaster.h"
#include "Enchant/Domain/Model/Namespace.h"

#include "Core/Domain/Gs2.h"

#include "Enchant/Model/Cache/RarityParameterModelMaster.h"
#include "Enchant/Model/Cache/Namespace.h"

namespace Gs2::Enchant::Domain::Iterator
{

    FDescribeRarityParameterModelMastersIterator::FDescribeRarityParameterModelMastersIterator(
        const TSharedPtr<Core::Domain::FGs2> Gs2,
        const Gs2::Enchant::FGs2EnchantRestClientPtr Client,
        const TOptional<FString> NamespaceName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(Client),
        NamespaceName(NamespaceName)
    {
    }

    FDescribeRarityParameterModelMastersIterator::FDescribeRarityParameterModelMastersIterator(
        const FDescribeRarityParameterModelMastersIterator& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        NamespaceName(From.NamespaceName)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDescribeRarityParameterModelMastersIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::Enchant::Model::FRarityParameterModelMaster>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FDescribeRarityParameterModelMastersIterator::FIterator::FIterator(
        const TSharedRef<FDescribeRarityParameterModelMastersIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        PageToken(TOptional<FString>()),
        FetchSize(TOptional<int32>())
    {
    }

    FDescribeRarityParameterModelMastersIterator::FIterator& FDescribeRarityParameterModelMastersIterator::FIterator::operator++()
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
            const auto ListParentKey = Gs2::Enchant::Model::Cache::FRarityParameterModelMasterCache::CreateCacheParentKey(
                Self->NamespaceName,
                TOptional<int32>()
            );
            if (!RangeIteratorOpt)
            {
                Range = Self->Gs2->Cache->TryGetList<Gs2::Enchant::Model::FRarityParameterModelMaster>(ListParentKey);

                if (Range)
                {
                    bLast = true;
                    RangeIteratorOpt = Range->CreateIterator();
                    PageToken = TOptional<FString>();
                    bEnd = !static_cast<bool>(*RangeIteratorOpt) && bLast;
                    return *this;
                }
            }
            const auto Request =
                MakeShared<Gs2::Enchant::Request::FDescribeRarityParameterModelMastersRequest>()
                    ->WithContextStack(Self->Gs2->DefaultContextStack)
                    ->WithNamespaceName(Self->NamespaceName)
                    ->WithPageToken(PageToken)
                    ->WithLimit(FetchSize)
            ;
            const auto Future = Self->Client->DescribeRarityParameterModelMasters(Request);
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
            Range = R->GetItems().IsValid() ? R->GetItems() : MakeShared<TArray<Gs2::Enchant::Model::FRarityParameterModelMasterPtr>>();
            const auto ResultModel = R;


            if (Range.IsValid())
            {
                for (const auto& Item : *Range)
                {
                    if (!Item.IsValid()) continue;
                    Gs2::Enchant::Model::Cache::FRarityParameterModelMasterCache::Put(
                        Self->Gs2->Cache,
                        Request->GetNamespaceName(), Item->GetName(),
                        TOptional<int32>(), Item
                    );
                }
            }
            if (Range)
            {
            }
            RangeIteratorOpt = Range->CreateIterator();
            PageToken = R->GetNextPageToken();
            bLast = !PageToken.IsSet();
            if (bLast) {
                Self->Gs2->Cache->SetListCached(
                    Gs2::Enchant::Model::FRarityParameterModelMaster::TypeName,
                    ListParentKey
                );
            }
        }

        bEnd = bLast && !*RangeIteratorOpt;
        return *this;
    }

    FDescribeRarityParameterModelMastersIterator::FIterator FDescribeRarityParameterModelMastersIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FDescribeRarityParameterModelMastersIterator::FIterator FDescribeRarityParameterModelMastersIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FDescribeRarityParameterModelMastersIterator::FIterator FDescribeRarityParameterModelMastersIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

