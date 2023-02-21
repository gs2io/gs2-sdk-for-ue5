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

#include "Matchmaking/Domain/Iterator/DoMatchmakingIterator.h"
#include "Matchmaking/Domain/Model/Gathering.h"
#include "Matchmaking/Domain/Model/User.h"

namespace Gs2::Matchmaking::Domain::Iterator
{

    Gs2::Core::Model::FGs2ErrorPtr FDoMatchmakingIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<TArray<Gs2::Matchmaking::Model::FGatheringPtr>>> Result)
    {
        const auto Future = Self->Client->DoMatchmaking(
            MakeShared<Gs2::Matchmaking::Request::FDoMatchmakingRequest>()
                ->WithNamespaceName(Self->NamespaceName)
                ->WithAccessToken(Self->AccessToken == nullptr ? TOptional<FString>() : Self->AccessToken->GetToken())
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

    TSharedPtr<FAsyncTask<FDoMatchmakingIteratorLoadTask>>
    FDoMatchmakingIterator::Load()
    {
        return Gs2::Core::Util::New<FAsyncTask<FDoMatchmakingIteratorLoadTask>>(SharedThis(this));
    }

    FDoMatchmakingIterator::FDoMatchmakingIterator(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Matchmaking::FGs2MatchmakingRestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken,
        const Gs2::Matchmaking::Model::FPlayerPtr Player
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        Client(Client),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        Player(Player),
        MatchmakingContextToken(TOptional<FString>()),
        FetchSize(TOptional<int32>())
    {

    }
    const Gs2::Matchmaking::Model::FGatheringPtr& FDoMatchmakingIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::Matchmaking::Model::FGatheringPtr FDoMatchmakingIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FDoMatchmakingIterator::IteratorImpl& FDoMatchmakingIterator::IteratorImpl::operator++()
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

    FDoMatchmakingIterator::IteratorImpl FDoMatchmakingIterator::begin()
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
    FDoMatchmakingIterator::IteratorImpl FDoMatchmakingIterator::end()
    {
        return IteratorImpl(nullptr);
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

