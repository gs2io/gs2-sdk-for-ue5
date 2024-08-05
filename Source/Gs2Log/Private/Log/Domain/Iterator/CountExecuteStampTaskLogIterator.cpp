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

#include "Log/Domain/Iterator/CountExecuteStampTaskLogIterator.h"
#include "Log/Domain/Model/ExecuteStampTaskLog.h"
#include "Log/Domain/Model/Namespace.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Log::Domain::Iterator
{

    FCountExecuteStampTaskLogIterator::FCountExecuteStampTaskLogIterator(
        const TSharedPtr<Core::Domain::FGs2> Gs2,
        const Gs2::Log::FGs2LogRestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const TOptional<bool> Service,
        const TOptional<bool> Method,
        const TOptional<bool> UserId,
        const TOptional<bool> Action,
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
        Action(Action),
        Begin(Begin),
        End(End),
        LongTerm(LongTerm),
        TimeOffsetToken(TimeOffsetToken)
    {
    }

    FCountExecuteStampTaskLogIterator::FCountExecuteStampTaskLogIterator(
        const FCountExecuteStampTaskLogIterator& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        Service(From.Service),
        Method(From.Method),
        UserId(From.UserId),
        Action(From.Action),
        Begin(From.Begin),
        End(From.End),
        LongTerm(From.LongTerm),
        TimeOffsetToken(From.TimeOffsetToken)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCountExecuteStampTaskLogIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::Log::Model::FExecuteStampTaskLogCount>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FCountExecuteStampTaskLogIterator::FIterator::FIterator(
        const TSharedRef<FCountExecuteStampTaskLogIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        PageToken(TOptional<FString>()),
        FetchSize(TOptional<int32>())
    {
    }

    FCountExecuteStampTaskLogIterator::FIterator& FCountExecuteStampTaskLogIterator::FIterator::operator++()
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

            const auto Future = Self->Client->CountExecuteStampTaskLog(
                MakeShared<Gs2::Log::Request::FCountExecuteStampTaskLogRequest>()
                    ->WithNamespaceName(Self->NamespaceName)
                    ->WithService(Self->Service)
                    ->WithMethod(Self->Method)
                    ->WithUserId(Self->UserId)
                    ->WithAction(Self->Action)
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
            if (Range)
            {
            }
            RangeIteratorOpt = Range->CreateIterator();
            PageToken = R->GetNextPageToken();
            bLast = !PageToken.IsSet();
        }

        bEnd = bLast && !*RangeIteratorOpt;
        return *this;
    }

    FCountExecuteStampTaskLogIterator::FIterator FCountExecuteStampTaskLogIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FCountExecuteStampTaskLogIterator::FIterator FCountExecuteStampTaskLogIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FCountExecuteStampTaskLogIterator::FIterator FCountExecuteStampTaskLogIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

