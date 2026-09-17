
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

#include "Buff/Domain/Iterator/DescribeBuffEntryModelMastersIterator.h"
#include "Buff/Domain/Model/BuffEntryModelMaster.h"
#include "Buff/Domain/Model/Namespace.h"

#include "Core/Domain/Gs2.h"

#include "Buff/Model/Cache/BuffEntryModelMaster.h"
#include "Buff/Model/Cache/Namespace.h"

namespace Gs2::Buff::Domain::Iterator
{

    FDescribeBuffEntryModelMastersIterator::FDescribeBuffEntryModelMastersIterator(
        const TSharedPtr<Core::Domain::FGs2> Gs2,
        const Gs2::Buff::FGs2BuffRestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> NamePrefix
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(Client),
        NamespaceName(NamespaceName),
        NamePrefix(NamePrefix)
    {
    }

    FDescribeBuffEntryModelMastersIterator::FDescribeBuffEntryModelMastersIterator(
        const FDescribeBuffEntryModelMastersIterator& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        NamePrefix(From.NamePrefix)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDescribeBuffEntryModelMastersIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::Buff::Model::FBuffEntryModelMaster>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FDescribeBuffEntryModelMastersIterator::FIterator::FIterator(
        const TSharedRef<FDescribeBuffEntryModelMastersIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        PageToken(TOptional<FString>()),
        FetchSize(TOptional<int32>())
    {
    }

    FDescribeBuffEntryModelMastersIterator::FIterator& FDescribeBuffEntryModelMastersIterator::FIterator::operator++()
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
            const auto ListParentKey = Gs2::Buff::Model::Cache::FBuffEntryModelMasterCache::CreateCacheParentKey(
                Self->NamespaceName,
                TOptional<int32>()
            );
            if (!RangeIteratorOpt)
            {
                Range = Self->Gs2->Cache->TryGetList<Gs2::Buff::Model::FBuffEntryModelMaster>(ListParentKey);

                if (Range)
                {
                    Range->RemoveAll([this](const Gs2::Buff::Model::FBuffEntryModelMasterPtr& Item) { return Self->NamePrefix && !Item->GetName()->StartsWith(*Self->NamePrefix); });
                    bLast = true;
                    RangeIteratorOpt = Range->CreateIterator();
                    PageToken = TOptional<FString>();
                    bEnd = !static_cast<bool>(*RangeIteratorOpt) && bLast;
                    return *this;
                }
            }
            const auto Request =
                MakeShared<Gs2::Buff::Request::FDescribeBuffEntryModelMastersRequest>()
                    ->WithContextStack(Self->Gs2->DefaultContextStack)
                    ->WithNamespaceName(Self->NamespaceName)
                    ->WithPageToken(PageToken)
                    ->WithLimit(FetchSize)
            ;
            const auto Future = Self->Client->DescribeBuffEntryModelMasters(Request);
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
            Range = R->GetItems().IsValid() ? R->GetItems() : MakeShared<TArray<Gs2::Buff::Model::FBuffEntryModelMasterPtr>>();
            const auto ResultModel = R;


            if (Range.IsValid())
            {
                for (const auto& Item : *Range)
                {
                    if (!Item.IsValid()) continue;
                    Gs2::Buff::Model::Cache::FBuffEntryModelMasterCache::Put(
                        Self->Gs2->Cache,
                        Request->GetNamespaceName(), Item->GetName(),
                        TOptional<int32>(), Item
                    );
                }
            }
            if (Range)
            {
                Range->RemoveAll([this](const Gs2::Buff::Model::FBuffEntryModelMasterPtr& Item) { return Self->NamePrefix.IsSet() && !Item->GetName()->StartsWith(*Self->NamePrefix); });
            }
            RangeIteratorOpt = Range->CreateIterator();
            PageToken = R->GetNextPageToken();
            bLast = !PageToken.IsSet();
            if (bLast) {
                Self->Gs2->Cache->SetListCached(
                    Gs2::Buff::Model::FBuffEntryModelMaster::TypeName,
                    ListParentKey
                );
            }
        }

        bEnd = bLast && !*RangeIteratorOpt;
        return *this;
    }

    FDescribeBuffEntryModelMastersIterator::FIterator FDescribeBuffEntryModelMastersIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FDescribeBuffEntryModelMastersIterator::FIterator FDescribeBuffEntryModelMastersIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FDescribeBuffEntryModelMastersIterator::FIterator FDescribeBuffEntryModelMastersIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

