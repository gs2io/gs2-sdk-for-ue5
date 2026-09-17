
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

#include "Deploy/Domain/Iterator/DescribeEventsIterator.h"
#include "Deploy/Domain/Model/Event.h"
#include "Deploy/Domain/Model/Stack.h"

#include "Core/Domain/Gs2.h"

#include "Deploy/Model/Cache/Event.h"
#include "Deploy/Model/Cache/Stack.h"

namespace Gs2::Deploy::Domain::Iterator
{

    FDescribeEventsIterator::FDescribeEventsIterator(
        const TSharedPtr<Core::Domain::FGs2> Gs2,
        const Gs2::Deploy::FGs2DeployRestClientPtr Client,
        const TOptional<FString> StackName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(Client),
        StackName(StackName)
    {
    }

    FDescribeEventsIterator::FDescribeEventsIterator(
        const FDescribeEventsIterator& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        StackName(From.StackName)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDescribeEventsIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::Deploy::Model::FEvent>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FDescribeEventsIterator::FIterator::FIterator(
        const TSharedRef<FDescribeEventsIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        PageToken(TOptional<FString>()),
        FetchSize(TOptional<int32>())
    {
    }

    FDescribeEventsIterator::FIterator& FDescribeEventsIterator::FIterator::operator++()
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
            const auto ListParentKey = Gs2::Deploy::Model::Cache::FEventCache::CreateCacheParentKey(
                Self->StackName,
                TOptional<int32>()
            );
            if (!RangeIteratorOpt)
            {
                Range = Self->Gs2->Cache->TryGetList<Gs2::Deploy::Model::FEvent>(ListParentKey);

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
                MakeShared<Gs2::Deploy::Request::FDescribeEventsRequest>()
                    ->WithContextStack(Self->Gs2->DefaultContextStack)
                    ->WithStackName(Self->StackName)
                    ->WithPageToken(PageToken)
                    ->WithLimit(FetchSize)
            ;
            const auto Future = Self->Client->DescribeEvents(Request);
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
            Range = R->GetItems().IsValid() ? R->GetItems() : MakeShared<TArray<Gs2::Deploy::Model::FEventPtr>>();
            const auto ResultModel = R;


            if (Range.IsValid())
            {
                for (const auto& Item : *Range)
                {
                    if (!Item.IsValid()) continue;
                    Gs2::Deploy::Model::Cache::FEventCache::Put(
                        Self->Gs2->Cache,
                        Request->GetStackName(), Item->GetName(),
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
                    Gs2::Deploy::Model::FEvent::TypeName,
                    ListParentKey
                );
            }
        }

        bEnd = bLast && !*RangeIteratorOpt;
        return *this;
    }

    FDescribeEventsIterator::FIterator FDescribeEventsIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FDescribeEventsIterator::FIterator FDescribeEventsIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FDescribeEventsIterator::FIterator FDescribeEventsIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

