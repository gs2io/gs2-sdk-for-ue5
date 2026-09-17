
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

#include "Formation/Domain/Iterator/DescribePropertyFormModelsIterator.h"
#include "Formation/Domain/Model/PropertyFormModel.h"
#include "Formation/Domain/Model/Namespace.h"

#include "Core/Domain/Gs2.h"

#include "Formation/Model/Cache/PropertyFormModel.h"
#include "Formation/Model/Cache/Namespace.h"

namespace Gs2::Formation::Domain::Iterator
{

    FDescribePropertyFormModelsIterator::FDescribePropertyFormModelsIterator(
        const TSharedPtr<Core::Domain::FGs2> Gs2,
        const Gs2::Formation::FGs2FormationRestClientPtr Client,
        const TOptional<FString> NamespaceName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(Client),
        NamespaceName(NamespaceName)
    {
    }

    FDescribePropertyFormModelsIterator::FDescribePropertyFormModelsIterator(
        const FDescribePropertyFormModelsIterator& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        NamespaceName(From.NamespaceName)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDescribePropertyFormModelsIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::Formation::Model::FPropertyFormModel>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FDescribePropertyFormModelsIterator::FIterator::FIterator(
        const TSharedRef<FDescribePropertyFormModelsIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        FetchSize(TOptional<int32>())
    {
    }

    FDescribePropertyFormModelsIterator::FIterator& FDescribePropertyFormModelsIterator::FIterator::operator++()
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
            const auto ListParentKey = Gs2::Formation::Model::Cache::FPropertyFormModelCache::CreateCacheParentKey(
                Self->NamespaceName,
                TOptional<int32>()
            );
            if (!RangeIteratorOpt)
            {
                Range = Self->Gs2->Cache->TryGetList<Gs2::Formation::Model::FPropertyFormModel>(ListParentKey);

                if (Range)
                {
                    bLast = true;
                    RangeIteratorOpt = Range->CreateIterator();
                    bEnd = !static_cast<bool>(*RangeIteratorOpt) && bLast;
                    return *this;
                }
            }
            const auto Request =
                MakeShared<Gs2::Formation::Request::FDescribePropertyFormModelsRequest>()
                    ->WithContextStack(Self->Gs2->DefaultContextStack)
                    ->WithNamespaceName(Self->NamespaceName)
            ;
            const auto Future = Self->Client->DescribePropertyFormModels(Request);
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
            Range = R->GetItems().IsValid() ? R->GetItems() : MakeShared<TArray<Gs2::Formation::Model::FPropertyFormModelPtr>>();
            const auto ResultModel = R;


            if (Range.IsValid())
            {
                for (const auto& Item : *Range)
                {
                    if (!Item.IsValid()) continue;
                    Gs2::Formation::Model::Cache::FPropertyFormModelCache::Put(
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
                    Gs2::Formation::Model::FPropertyFormModel::TypeName,
                    ListParentKey
                );
            }
        }

        bEnd = bLast && !*RangeIteratorOpt;
        return *this;
    }

    FDescribePropertyFormModelsIterator::FIterator FDescribePropertyFormModelsIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FDescribePropertyFormModelsIterator::FIterator FDescribePropertyFormModelsIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FDescribePropertyFormModelsIterator::FIterator FDescribePropertyFormModelsIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

