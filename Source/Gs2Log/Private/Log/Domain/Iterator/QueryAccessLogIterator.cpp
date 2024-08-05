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

#include "Log/Domain/Iterator/QueryAccessLogIterator.h"
#include "Log/Domain/Model/AccessLog.h"
#include "Log/Domain/Model/Namespace.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Log::Domain::Iterator
{

    FQueryAccessLogIterator::FQueryAccessLogIterator(
        const TSharedPtr<Core::Domain::FGs2> Gs2,
        const Gs2::Log::FGs2LogRestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> Service,
        const TOptional<FString> Method,
        const TOptional<FString> UserId,
        const TOptional<int64> Begin,
        const TOptional<int64> End,
        const TOptional<bool> LongTerm,
        const TOptional<FString> TimeOffsetToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(Client),
        NamespaceName(NamespaceName),
        Service(Service),
        Method(Method),
        UserId(UserId),
        Begin(Begin),
        End(End),
        LongTerm(LongTerm),
        TimeOffsetToken(TimeOffsetToken)
    {
    }

    FQueryAccessLogIterator::FQueryAccessLogIterator(
        const FQueryAccessLogIterator& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        Service(From.Service),
        Method(From.Method),
        UserId(From.UserId),
        Begin(From.Begin),
        End(From.End),
        LongTerm(From.LongTerm),
        TimeOffsetToken(From.TimeOffsetToken)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FQueryAccessLogIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::Log::Model::FAccessLog>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FQueryAccessLogIterator::FIterator::FIterator(
        const TSharedRef<FQueryAccessLogIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        PageToken(TOptional<FString>()),
        FetchSize(TOptional<int32>())
    {
    }

    FQueryAccessLogIterator::FIterator& FQueryAccessLogIterator::FIterator::operator++()
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
            const auto ListParentKey = Gs2::Log::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                Self->NamespaceName,
                "AccessLog"
            );

            if (!RangeIteratorOpt)
            {
                Range = Self->Gs2->Cache->TryGetList<Gs2::Log::Model::FAccessLog>(ListParentKey);

                if (Range)
                {
                    Range->RemoveAll([this](const Gs2::Log::Model::FAccessLogPtr& Item) { return Self->Service && Item->GetService() != Self->Service; });
                    Range->RemoveAll([this](const Gs2::Log::Model::FAccessLogPtr& Item) { return Self->Method && Item->GetMethod() != Self->Method; });
                    Range->RemoveAll([this](const Gs2::Log::Model::FAccessLogPtr& Item) { return Self->UserId && Item->GetUserId() != Self->UserId; });
                    Range->RemoveAll([this](const Gs2::Log::Model::FAccessLogPtr& Item) { return Self->Begin && *Item->GetTimestamp() < *Self->Begin; });
                    Range->RemoveAll([this](const Gs2::Log::Model::FAccessLogPtr& Item) { return Self->End && *Item->GetTimestamp() > *Self->End; });
                    bLast = true;
                    RangeIteratorOpt = Range->CreateIterator();
                    PageToken = TOptional<FString>();
                    bEnd = !static_cast<bool>(*RangeIteratorOpt) && bLast;
                    return *this;
                }
            }

            const auto Future = Self->Client->QueryAccessLog(
                MakeShared<Gs2::Log::Request::FQueryAccessLogRequest>()
                    ->WithNamespaceName(Self->NamespaceName)
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
                    Gs2::Log::Model::FAccessLog::TypeName,
                    ListParentKey,
                    Gs2::Log::Domain::Model::FAccessLogDomain::CreateCacheKey(
                    ),
                    Item,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (Range)
            {
                Range->RemoveAll([this](const Gs2::Log::Model::FAccessLogPtr& Item) { return Self->Service && Item->GetService() != Self->Service; });
                Range->RemoveAll([this](const Gs2::Log::Model::FAccessLogPtr& Item) { return Self->Method && Item->GetMethod() != Self->Method; });
                Range->RemoveAll([this](const Gs2::Log::Model::FAccessLogPtr& Item) { return Self->UserId && Item->GetUserId() != Self->UserId; });
                Range->RemoveAll([this](const Gs2::Log::Model::FAccessLogPtr& Item) { return Self->Begin && *Item->GetTimestamp() < *Self->Begin; });
                Range->RemoveAll([this](const Gs2::Log::Model::FAccessLogPtr& Item) { return Self->End && *Item->GetTimestamp() > *Self->End; });
            }
            RangeIteratorOpt = Range->CreateIterator();
            PageToken = R->GetNextPageToken();
            bLast = !PageToken.IsSet();
            if (bLast) {
                Self->Gs2->Cache->SetListCached(
                    Gs2::Log::Model::FAccessLog::TypeName,
                    ListParentKey
                );
            }
        }

        bEnd = bLast && !*RangeIteratorOpt;
        return *this;
    }

    FQueryAccessLogIterator::FIterator FQueryAccessLogIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FQueryAccessLogIterator::FIterator FQueryAccessLogIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FQueryAccessLogIterator::FIterator FQueryAccessLogIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

