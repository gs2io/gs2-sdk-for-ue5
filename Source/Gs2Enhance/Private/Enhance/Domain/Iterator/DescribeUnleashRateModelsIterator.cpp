
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

#include "Enhance/Domain/Iterator/DescribeUnleashRateModelsIterator.h"
#include "Enhance/Domain/Model/UnleashRateModel.h"
#include "Enhance/Domain/Model/Namespace.h"

#include "Core/Domain/Gs2.h"

#include "Enhance/Model/Cache/UnleashRateModel.h"
#include "Enhance/Model/Cache/Namespace.h"

namespace Gs2::Enhance::Domain::Iterator
{

    FDescribeUnleashRateModelsIterator::FDescribeUnleashRateModelsIterator(
        const TSharedPtr<Core::Domain::FGs2> Gs2,
        const Gs2::Enhance::FGs2EnhanceRestClientPtr Client,
        const TOptional<FString> NamespaceName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(Client),
        NamespaceName(NamespaceName)
    {
    }

    FDescribeUnleashRateModelsIterator::FDescribeUnleashRateModelsIterator(
        const FDescribeUnleashRateModelsIterator& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        NamespaceName(From.NamespaceName)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDescribeUnleashRateModelsIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::Enhance::Model::FUnleashRateModel>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FDescribeUnleashRateModelsIterator::FIterator::FIterator(
        const TSharedRef<FDescribeUnleashRateModelsIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        FetchSize(TOptional<int32>())
    {
    }

    FDescribeUnleashRateModelsIterator::FIterator& FDescribeUnleashRateModelsIterator::FIterator::operator++()
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
            const auto ListParentKey = Gs2::Enhance::Model::Cache::FUnleashRateModelCache::CreateCacheParentKey(
                Self->NamespaceName,
                TOptional<int32>()
            );
            if (!RangeIteratorOpt)
            {
                Range = Self->Gs2->Cache->TryGetList<Gs2::Enhance::Model::FUnleashRateModel>(ListParentKey);

                if (Range)
                {
                    bLast = true;
                    RangeIteratorOpt = Range->CreateIterator();
                    bEnd = !static_cast<bool>(*RangeIteratorOpt) && bLast;
                    return *this;
                }
            }
            const auto Request =
                MakeShared<Gs2::Enhance::Request::FDescribeUnleashRateModelsRequest>()
                    ->WithContextStack(Self->Gs2->DefaultContextStack)
                    ->WithNamespaceName(Self->NamespaceName)
            ;
            const auto Future = Self->Client->DescribeUnleashRateModels(Request);
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
            Range = R->GetItems().IsValid() ? R->GetItems() : MakeShared<TArray<Gs2::Enhance::Model::FUnleashRateModelPtr>>();
            const auto ResultModel = R;


            if (Range.IsValid())
            {
                for (const auto& Item : *Range)
                {
                    if (!Item.IsValid()) continue;
                    Gs2::Enhance::Model::Cache::FUnleashRateModelCache::Put(
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
            bLast = true;
            if (bLast) {
                Self->Gs2->Cache->SetListCached(
                    Gs2::Enhance::Model::FUnleashRateModel::TypeName,
                    ListParentKey
                );
            }
        }

        bEnd = bLast && !*RangeIteratorOpt;
        return *this;
    }

    FDescribeUnleashRateModelsIterator::FIterator FDescribeUnleashRateModelsIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FDescribeUnleashRateModelsIterator::FIterator FDescribeUnleashRateModelsIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FDescribeUnleashRateModelsIterator::FIterator FDescribeUnleashRateModelsIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

