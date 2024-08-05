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
 *
 * deny overwrite
 */

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

// ReSharper disable CppUnusedIncludeDirective

#include "Log/Domain/Iterator/QueryInGameLogIterator.h"
#include "Log/Domain/Model/InGameLog.h"
#include "Log/Domain/Model/User.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Log::Domain::Iterator
{

    FQueryInGameLogIterator::FQueryInGameLogIterator(
        const TSharedPtr<Core::Domain::FGs2> Gs2,
        const Gs2::Log::FGs2LogRestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TSharedPtr<TArray<TSharedPtr<Log::Model::FInGameLogTag>>> Tags,
        const TOptional<int64> Begin,
        const TOptional<int64> End,
        const TOptional<bool> LongTerm,
        const TOptional<FString> TimeOffsetToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(Client),
        NamespaceName(NamespaceName),
        UserId(UserId),
        Tags(Tags),
        Begin(Begin),
        End(End),
        LongTerm(LongTerm),
        TimeOffsetToken(TimeOffsetToken)
    {
    }

    FQueryInGameLogIterator::FQueryInGameLogIterator(
        const FQueryInGameLogIterator& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        Tags(From.Tags),
        Begin(From.Begin),
        End(From.End),
        LongTerm(From.LongTerm),
        TimeOffsetToken(From.TimeOffsetToken)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FQueryInGameLogIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::Log::Model::FInGameLog>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FQueryInGameLogIterator::FIterator::FIterator(
        const TSharedRef<FQueryInGameLogIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        PageToken(TOptional<FString>()),
        FetchSize(TOptional<int32>())
    {
    }

    FQueryInGameLogIterator::FIterator& FQueryInGameLogIterator::FIterator::operator++()
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
            const auto ListParentKey = Gs2::Log::Domain::Model::FUserDomain::CreateCacheParentKey(
                Self->NamespaceName,
                Self->UserId,
                "InGameLog"
            );

            if (!RangeIteratorOpt)
            {
                Range = Self->Gs2->Cache->TryGetList<Gs2::Log::Model::FInGameLog>(ListParentKey);

                if (Range)
                {
                    Range->RemoveAll([this](const Gs2::Log::Model::FInGameLogPtr& Item) { return Self->Begin && *Item->GetTimestamp() < *Self->Begin; });
                    Range->RemoveAll([this](const Gs2::Log::Model::FInGameLogPtr& Item) { return Self->End && *Item->GetTimestamp() > *Self->End; });
                    bLast = true;
                    RangeIteratorOpt = Range->CreateIterator();
                    PageToken = TOptional<FString>();
                    bEnd = !static_cast<bool>(*RangeIteratorOpt) && bLast;
                    return *this;
                }
            }

            const auto Future = Self->Client->QueryInGameLog(
                MakeShared<Gs2::Log::Request::FQueryInGameLogRequest>()
                    ->WithNamespaceName(Self->NamespaceName)
                    ->WithUserId(Self->UserId)
                    ->WithBegin(Self->Begin)
                    ->WithEnd(Self->End)
                    ->WithLongTerm(Self->LongTerm)
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
                Self->Gs2->Cache->Put(
                    Gs2::Log::Model::FInGameLog::TypeName,
                    ListParentKey,
                    Gs2::Log::Domain::Model::FInGameLogDomain::CreateCacheKey(
                        Item->GetRequestId()
                    ),
                    Item,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (Range)
            {
                Range->RemoveAll([this](const Gs2::Log::Model::FInGameLogPtr& Item) { return Self->Begin && *Item->GetTimestamp() < *Self->Begin; });
                Range->RemoveAll([this](const Gs2::Log::Model::FInGameLogPtr& Item) { return Self->End && *Item->GetTimestamp() > *Self->End; });
            }
            RangeIteratorOpt = Range->CreateIterator();
            PageToken = R->GetNextPageToken();
            bLast = !PageToken.IsSet();
            if (bLast) {
                Self->Gs2->Cache->SetListCached(
                    Gs2::Log::Model::FInGameLog::TypeName,
                    ListParentKey
                );
            }
        }

        bEnd = bLast && !*RangeIteratorOpt;
        return *this;
    }

    FQueryInGameLogIterator::FIterator FQueryInGameLogIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FQueryInGameLogIterator::FIterator FQueryInGameLogIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FQueryInGameLogIterator::FIterator FQueryInGameLogIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

