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

#include "Matchmaking/Domain/Iterator/DoMatchmakingByUserIdIterator.h"
#include "Matchmaking/Domain/Model/Gathering.h"
#include "Matchmaking/Domain/Model/User.h"

namespace Gs2::Matchmaking::Domain::Iterator
{

    Gs2::Core::Model::FGs2ErrorPtr FDoMatchmakingByUserIdIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<TArray<Gs2::Matchmaking::Model::FGatheringPtr>>> Result)
    {
        const auto Future = Self->Client->DoMatchmakingByUserId(
            MakeShared<Gs2::Matchmaking::Request::FDoMatchmakingByUserIdRequest>()
                ->WithNamespaceName(Self->NamespaceName)
                ->WithUserId(Self->UserId)
                ->WithPlayer(Self->Player)
                ->WithMatchmakingContextToken(Self->MatchmakingContextToken)
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto R = Future->GetTask().Result();
        Future->EnsureCompletion();
        auto Arr = MakeShared<TArray<Gs2::Matchmaking::Model::FGatheringPtr>>();
        Arr->Add(R->GetItem());
        *Result = Arr;
        Self->MatchmakingContextToken = R->GetMatchmakingContextToken();
        Self->Last = !Self->MatchmakingContextToken.IsSet();
        Self->Cache->ClearListCache<Gs2::Matchmaking::Model::FGathering>(
            Gs2::Matchmaking::Domain::Model::FUserDomain::CreateCacheParentKey(
                Self->NamespaceName,
                TOptional<FString>("Singleton"),
                "Gathering"
            )
        );
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDoMatchmakingByUserIdIteratorLoadTask>>
    FDoMatchmakingByUserIdIterator::Load()
    {
        return Gs2::Core::Util::New<FAsyncTask<FDoMatchmakingByUserIdIteratorLoadTask>>(SharedThis(this));
    }

    FDoMatchmakingByUserIdIterator::FDoMatchmakingByUserIdIterator(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Matchmaking::FGs2MatchmakingRestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const Gs2::Matchmaking::Model::FPlayerPtr Player
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        Client(Client),
        NamespaceName(NamespaceName),
        UserId(UserId),
        Player(Player),
        MatchmakingContextToken(TOptional<FString>()),
        FetchSize(TOptional<int32>())
    {

    }
    const Gs2::Matchmaking::Model::FGatheringPtr& FDoMatchmakingByUserIdIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::Matchmaking::Model::FGatheringPtr FDoMatchmakingByUserIdIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FDoMatchmakingByUserIdIterator::IteratorImpl& FDoMatchmakingByUserIdIterator::IteratorImpl::operator++()
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

    FDoMatchmakingByUserIdIterator::IteratorImpl FDoMatchmakingByUserIdIterator::begin()
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
    FDoMatchmakingByUserIdIterator::IteratorImpl FDoMatchmakingByUserIdIterator::end()
    {
        return IteratorImpl(nullptr);
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

