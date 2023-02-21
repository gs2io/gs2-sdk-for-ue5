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

#include "Lottery/Domain/Iterator/DescribeProbabilitiesByUserIdIterator.h"
#include "Lottery/Domain/Model/Probability.h"
#include "Lottery/Domain/Model/User.h"

namespace Gs2::Lottery::Domain::Iterator
{

    Gs2::Core::Model::FGs2ErrorPtr FDescribeProbabilitiesByUserIdIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<TArray<Gs2::Lottery::Model::FProbabilityPtr>>> Result)
    {
        const auto Future = Self->Client->DescribeProbabilitiesByUserId(
            MakeShared<Gs2::Lottery::Request::FDescribeProbabilitiesByUserIdRequest>()
                ->WithNamespaceName(Self->NamespaceName)
                ->WithLotteryName(Self->LotteryName)
                ->WithUserId(Self->UserId)
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto R = Future->GetTask().Result();
        Future->EnsureCompletion();
        *Result = R->GetItems();
        Self->Last = true;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDescribeProbabilitiesByUserIdIteratorLoadTask>>
    FDescribeProbabilitiesByUserIdIterator::Load()
    {
        return Gs2::Core::Util::New<FAsyncTask<FDescribeProbabilitiesByUserIdIteratorLoadTask>>(SharedThis(this));
    }

    FDescribeProbabilitiesByUserIdIterator::FDescribeProbabilitiesByUserIdIterator(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Lottery::FGs2LotteryRestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> LotteryName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        Client(Client),
        NamespaceName(NamespaceName),
        LotteryName(LotteryName),
        UserId(UserId),
        FetchSize(TOptional<int32>())
    {

    }
    const Gs2::Lottery::Model::FProbabilityPtr& FDescribeProbabilitiesByUserIdIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::Lottery::Model::FProbabilityPtr FDescribeProbabilitiesByUserIdIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FDescribeProbabilitiesByUserIdIterator::IteratorImpl& FDescribeProbabilitiesByUserIdIterator::IteratorImpl::operator++()
    {
        Task->StartSynchronousTask();
        Current = nullptr;
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Current = Task->GetTask().Result();
        }
        Task->EnsureCompletion();
        return *this;
    }

    FDescribeProbabilitiesByUserIdIterator::IteratorImpl FDescribeProbabilitiesByUserIdIterator::begin()
    {
        const auto Task = Next();
        IteratorImpl Impl(Task);
        Task->StartSynchronousTask();
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Impl.Current = Task->GetTask().Result();
        }
        Task->EnsureCompletion();
        return Impl;
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    FDescribeProbabilitiesByUserIdIterator::IteratorImpl FDescribeProbabilitiesByUserIdIterator::end()
    {
        return IteratorImpl(nullptr);
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

