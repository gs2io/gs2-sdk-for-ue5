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

#include "MegaField/Domain/Iterator/DescribeLayerModelsIterator.h"
#include "MegaField/Domain/Model/LayerModel.h"
#include "MegaField/Domain/Model/AreaModel.h"

namespace Gs2::MegaField::Domain::Iterator
{

    FDescribeLayerModelsIterator::FDescribeLayerModelsIterator(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::MegaField::FGs2MegaFieldRestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> AreaModelName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        Client(Client),
        NamespaceName(NamespaceName),
        AreaModelName(AreaModelName)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDescribeLayerModelsIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::MegaField::Model::FLayerModel>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FDescribeLayerModelsIterator::FIterator::FIterator(
        const TSharedRef<FDescribeLayerModelsIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        FetchSize(TOptional<int32>())
    {
    }

    FDescribeLayerModelsIterator::FIterator& FDescribeLayerModelsIterator::FIterator::operator++()
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
            const auto ListParentKey = Gs2::MegaField::Domain::Model::FAreaModelDomain::CreateCacheParentKey(
                Self->NamespaceName,
                Self->AreaModelName,
                "LayerModel"
            );
            Range = Self->Cache->TryGetList<Gs2::MegaField::Model::FLayerModel>(ListParentKey);
            if (Range) {
                RangeIteratorOpt = Range->CreateIterator();
                bLast = true;
                bEnd = !static_cast<bool>(*RangeIteratorOpt);
                return *this;
            }
            const auto Future = Self->Client->DescribeLayerModels(
                MakeShared<Gs2::MegaField::Request::FDescribeLayerModelsRequest>()
                    ->WithNamespaceName(Self->NamespaceName)
                    ->WithAreaModelName(Self->AreaModelName)
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
                    Gs2::MegaField::Model::FLayerModel::TypeName,
                    ListParentKey,
                    Gs2::MegaField::Domain::Model::FLayerModelDomain::CreateCacheKey(
                        Item->GetName()
                    ),
                    Item,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            RangeIteratorOpt = Range->CreateIterator();
            bLast = true;
            if (bLast) {
                Self->Cache->SetListCache(
                    Gs2::MegaField::Model::FLayerModel::TypeName,
                    ListParentKey
                );
            }
        }

        bEnd = bLast && !*RangeIteratorOpt;
        return *this;
    }

    FDescribeLayerModelsIterator::FIterator FDescribeLayerModelsIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FDescribeLayerModelsIterator::FIterator FDescribeLayerModelsIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FDescribeLayerModelsIterator::FIterator FDescribeLayerModelsIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

