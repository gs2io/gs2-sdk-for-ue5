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

#include "Auth/Domain/Gs2Auth.h"
#include "Guild/Domain/Model/UserAccessToken.h"
#include "Guild/Domain/Model/User.h"
#include "Guild/Domain/Model/Namespace.h"
#include "Guild/Domain/Model/GuildModelMaster.h"
#include "Guild/Domain/Model/GuildModel.h"
#include "Guild/Domain/Model/User.h"
#include "Guild/Domain/Model/UserAccessToken.h"
#include "Guild/Domain/Model/Guild.h"
#include "Guild/Domain/Model/JoinedGuild.h"
#include "Guild/Domain/Model/JoinedGuildAccessToken.h"
#include "Guild/Domain/Model/CurrentGuildMaster.h"
#include "Guild/Domain/Model/ReceiveMemberRequest.h"
#include "Guild/Domain/Model/SendMemberRequest.h"
#include "Guild/Domain/Model/SendMemberRequestAccessToken.h"
#include "Guild/Model/Cache/SendMemberRequest.h"
#include "Guild/Model/Cache/JoinedGuild.h"


#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Guild::Domain::Model
{

    FUserAccessTokenDomain::FUserAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Guild::Domain::FGs2GuildDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Guild::FGs2GuildRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        ParentKey(Gs2::Guild::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "User"
        ))
    {
    }

    FUserAccessTokenDomain::FUserAccessTokenDomain(
        const FUserAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        ParentKey(From.ParentKey)
    {

    }

    FUserAccessTokenDomain::FCreateGuildTask::FCreateGuildTask(
        const TSharedPtr<FUserAccessTokenDomain>& Self,
        const Request::FCreateGuildRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserAccessTokenDomain::FCreateGuildTask::FCreateGuildTask(
        const FCreateGuildTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserAccessTokenDomain::FCreateGuildTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FGuildDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto Future = Self->Client->CreateGuild(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Guild::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "Guild"
                );
                const auto Key = Gs2::Guild::Domain::Model::FGuildDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetGuildModelName(),
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Guild::Model::FGuild::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Guild::Domain::Model::FGuildDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetGuildModelName(),
            ResultModel->GetItem()->GetName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserAccessTokenDomain::FCreateGuildTask>> FUserAccessTokenDomain::CreateGuild(
        Request::FCreateGuildRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateGuildTask>>(this->AsShared(), Request);
    }

    FUserAccessTokenDomain::FAssumeTask::FAssumeTask(
        const TSharedPtr<FUserAccessTokenDomain>& Self,
        const Request::FAssumeRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserAccessTokenDomain::FAssumeTask::FAssumeTask(
        const FAssumeTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserAccessTokenDomain::FAssumeTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Auth::Domain::Model::FAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto Future = Self->Client->Assume(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
        }
        const auto Domain = Self->Gs2->Auth->AccessToken();
        if (ResultModel != nullptr)
        {
            if (ResultModel->GetToken().IsSet())
            {
                Domain->Token = ResultModel->GetToken();
            }
            if (ResultModel->GetUserId().IsSet())
            {
                Domain->UserId = ResultModel->GetUserId();
            }
            if (ResultModel->GetExpire().IsSet())
            {
                Domain->Expire = ResultModel->GetExpire();
            }
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserAccessTokenDomain::FAssumeTask>> FUserAccessTokenDomain::Assume(
        Request::FAssumeRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FAssumeTask>>(this->AsShared(), Request);
    }

    FUserAccessTokenDomain::FSendRequestTask::FSendRequestTask(
        const TSharedPtr<FUserAccessTokenDomain>& Self,
        const Request::FSendRequestRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserAccessTokenDomain::FSendRequestTask::FSendRequestTask(
        const FSendRequestTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserAccessTokenDomain::FSendRequestTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FGuildDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto Future = Self->Client->SendRequest(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Guild::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "Guild"
                );
                const auto Key = Gs2::Guild::Domain::Model::FGuildDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetGuildModelName(),
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Guild::Model::FGuild::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetSendMemberRequest() != nullptr)
            {
                Gs2::Guild::Model::Cache::FSendMemberRequestCache::Put(

                    Self->Gs2->Cache, Self->NamespaceName, Self->UserId(), RequestModel->GetGuildModelName(),

                    ResultModel->GetSendMemberRequest()->GetTargetGuildName(), Self->AccessToken->GetTimeOffset(), ResultModel->GetSendMemberRequest()

                );
            }
        }
        auto Domain = MakeShared<Gs2::Guild::Domain::Model::FGuildDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            RequestModel->GetGuildModelName(),
            RequestModel->GetTargetGuildName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserAccessTokenDomain::FSendRequestTask>> FUserAccessTokenDomain::SendRequest(
        Request::FSendRequestRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FSendRequestTask>>(this->AsShared(), Request);
    }

    FUserAccessTokenDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FUserAccessTokenDomain>& Self,
        const Request::FDeleteRequestRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserAccessTokenDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserAccessTokenDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FSendMemberRequestAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto Future = Self->Client->DeleteRequest(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                Gs2::Guild::Model::Cache::FSendMemberRequestCache::Delete(

                    Self->Gs2->Cache, Self->NamespaceName, Self->UserId(), RequestModel->GetGuildModelName(),

                    ResultModel->GetItem()->GetTargetGuildName(), Self->AccessToken->GetTimeOffset()

                );
            }
        }
        auto Domain = MakeShared<Gs2::Guild::Domain::Model::FSendMemberRequestAccessTokenDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            Self->AccessToken,
            Request->GetGuildModelName(),
            Request->GetTargetGuildName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserAccessTokenDomain::FDeleteTask>> FUserAccessTokenDomain::Delete(
        Request::FDeleteRequestRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    Gs2::Guild::Domain::Iterator::FDescribeSendRequestsIteratorPtr FUserAccessTokenDomain::SendRequests(
        const FString GuildModelName
    ) const
    {
        return MakeShared<Gs2::Guild::Domain::Iterator::FDescribeSendRequestsIterator>(
            Gs2,
            Client,
            NamespaceName,
            AccessToken,
            GuildModelName
        );
    }

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeSendRequests(

        TFunction<void()> Callback,

        const FString GuildModelName

    )

    {

        return Gs2::Guild::Model::Cache::FSendMemberRequestCache::ListSubscribe(

            Gs2->Cache, NamespaceName, GuildModelName, UserId(), AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>(),

            [Callback](const TArray<Gs2::Guild::Model::FSendMemberRequestPtr>&) { Callback(); }

        );

    }



    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeSendRequests(
        const FString GuildModelName,
        TFunction<void()> Callback
    )
    {
        return SubscribeSendRequests(Callback, GuildModelName);

    }

    void FUserAccessTokenDomain::UnsubscribeSendRequests(
        const FString GuildModelName,
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2::Guild::Model::Cache::FSendMemberRequestCache::ListUnsubscribe(

            Gs2->Cache, NamespaceName, GuildModelName, UserId(), AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>(), CallbackID

        );
    }

    class FUserAccessTokenDomain::FCollectSendRequestsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Guild::Model::FSendMemberRequestPtr>>, public TSharedFromThis<FCollectSendRequestsTask>

    {

        const TSharedPtr<FUserAccessTokenDomain> Self;

        const TFunction<void(TArray<Gs2::Guild::Model::FSendMemberRequestPtr>)> OnCollected;

        const FString QueryGuildModelName;

    public:

        FCollectSendRequestsTask(const TSharedPtr<FUserAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Guild::Model::FSendMemberRequestPtr>)> OnCollected, const FString GuildModelName): Self(Self), OnCollected(OnCollected), QueryGuildModelName(GuildModelName) {}

        FCollectSendRequestsTask(const FCollectSendRequestsTask& From): TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryGuildModelName(From.QueryGuildModelName) {}

        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Guild::Model::FSendMemberRequestPtr>>> Result) override

        {

            TArray<Gs2::Guild::Model::FSendMemberRequestPtr> Items;

            auto Iterator = Self->SendRequests(QueryGuildModelName)->begin();

            while (Iterator.HasNext()) { if (Iterator.IsError()) return Iterator.Error(); if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current()); ++Iterator; }

            if (Iterator.IsError()) return Iterator.Error();

            *Result = MakeShared<TArray<Gs2::Guild::Model::FSendMemberRequestPtr>>(Items);

            if (OnCollected) OnCollected(Items);

            return nullptr;

        }

    };



    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeSendRequests(

        TFunction<void(TArray<Gs2::Guild::Model::FSendMemberRequestPtr>)> Callback,

        const FString GuildModelName

    )

    {

        const auto Parent = Gs2::Guild::Model::Cache::FSendMemberRequestCache::CreateCacheParentKey(NamespaceName, GuildModelName, UserId(), AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>());

        const auto WeakGs2 = this->Gs2;

        const auto WeakService = this->Service;

        const auto SourceToken = this->AccessToken;

        const auto QueryNamespaceName = this->NamespaceName;

        return Gs2->Cache->ListSubscribeTyped(

            Gs2::Guild::Model::FSendMemberRequest::TypeName, Parent,

            [Callback](const TArray<FGs2ObjectPtr>& Values) { TArray<Gs2::Guild::Model::FSendMemberRequestPtr> Items; for (const auto& Value : Values) if (Value.IsValid()) Items.Add(StaticCastSharedPtr<Gs2::Guild::Model::FSendMemberRequest>(Value)); Callback(Items); },

            [WeakGs2, WeakService, Callback, GuildModelName, SourceToken, QueryNamespaceName]() { if (!WeakGs2.IsValid() || !SourceToken.IsValid()) return; const auto Domain = MakeShared<FUserAccessTokenDomain>(WeakGs2, WeakService, QueryNamespaceName, SourceToken); const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectSendRequestsTask>>(Domain, Callback, GuildModelName); Task->StartBackgroundTask(); }

        );

    }



    void FUserAccessTokenDomain::InvalidateSendRequests(const FString GuildModelName)

    {

        Gs2->Cache->ClearListCache(Gs2::Guild::Model::FSendMemberRequest::TypeName, Gs2::Guild::Model::Cache::FSendMemberRequestCache::CreateCacheParentKey(NamespaceName, GuildModelName, UserId(), AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()));

    }



    FUserAccessTokenDomain::FSubscribeSendRequestsWithInitialCallTask::FSubscribeSendRequestsWithInitialCallTask(const TSharedPtr<FUserAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Guild::Model::FSendMemberRequestPtr>)> Callback, const FString GuildModelName): Self(Self), Callback(Callback), QueryGuildModelName(GuildModelName) {}

    FUserAccessTokenDomain::FSubscribeSendRequestsWithInitialCallTask::FSubscribeSendRequestsWithInitialCallTask(const FSubscribeSendRequestsWithInitialCallTask& From): TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryGuildModelName(From.QueryGuildModelName) {}

    Gs2::Core::Model::FGs2ErrorPtr FUserAccessTokenDomain::FSubscribeSendRequestsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)

    {

        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectSendRequestsTask>>(Self, TFunction<void(TArray<Gs2::Guild::Model::FSendMemberRequestPtr>)>(), QueryGuildModelName); Task->StartSynchronousTask(); Task->EnsureCompletion(); if (Task->GetTask().IsError()) return Task->GetTask().Error(); const auto Values = Task->GetTask().Result(); const auto CallbackId = Self->SubscribeSendRequests(Callback, QueryGuildModelName); Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId); return nullptr;

    }

    TSharedPtr<FAsyncTask<FUserAccessTokenDomain::FSubscribeSendRequestsWithInitialCallTask>> FUserAccessTokenDomain::SubscribeSendRequestsWithInitialCall(TFunction<void(TArray<Gs2::Guild::Model::FSendMemberRequestPtr>)> Callback, const FString GuildModelName)

    {

        return Gs2::Core::Util::New<FAsyncTask<FSubscribeSendRequestsWithInitialCallTask>>(this->AsShared(), Callback, GuildModelName);

    }



    TSharedPtr<Gs2::Guild::Domain::Model::FSendMemberRequestAccessTokenDomain> FUserAccessTokenDomain::SendMemberRequest(
        const FString GuildModelName,
        const FString GuildName
    )
    {
        return MakeShared<Gs2::Guild::Domain::Model::FSendMemberRequestAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            GuildModelName == TEXT("") ? TOptional<FString>() : TOptional<FString>(GuildModelName),
            GuildName == TEXT("") ? TOptional<FString>() : TOptional<FString>(GuildName)
        );
    }

    Gs2::Guild::Domain::Iterator::FSearchGuildsIteratorPtr FUserAccessTokenDomain::SearchGuilds(
        const FString GuildModelName,
        const TOptional<FString> DisplayName,
        const TSharedPtr<TArray<int32>> Attributes1,
        const TSharedPtr<TArray<int32>> Attributes2,
        const TSharedPtr<TArray<int32>> Attributes3,
        const TSharedPtr<TArray<int32>> Attributes4,
        const TSharedPtr<TArray<int32>> Attributes5,
        const TSharedPtr<TArray<FString>> JoinPolicies,
        const TOptional<bool> IncludeFullMembersGuild,
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Guild::Domain::Iterator::FSearchGuildsIterator>(
            Gs2,
            Client,
            NamespaceName,
            GuildModelName,
            AccessToken,
            DisplayName,
            Attributes1,
            Attributes2,
            Attributes3,
            Attributes4,
            Attributes5,
            JoinPolicies,
            IncludeFullMembersGuild
        );
    }

    Gs2::Guild::Domain::Iterator::FDescribeJoinedGuildsIteratorPtr FUserAccessTokenDomain::JoinedGuilds(
        const TOptional<FString> GuildModelName
    ) const
    {
        return MakeShared<Gs2::Guild::Domain::Iterator::FDescribeJoinedGuildsIterator>(
            Gs2,
            Client,
            NamespaceName,
            AccessToken,
            GuildModelName
        );
    }

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeJoinedGuilds(
    TFunction<void()> Callback
        , const TOptional<FString> GuildModelName
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Guild::Model::FJoinedGuild::TypeName,
            Gs2::Guild::Model::Cache::FJoinedGuildCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FUserAccessTokenDomain::UnsubscribeJoinedGuilds(

        Gs2::Core::Domain::CallbackID CallbackID, const TOptional<FString> GuildModelName
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Guild::Model::FJoinedGuild::TypeName,
            Gs2::Guild::Model::Cache::FJoinedGuildCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FUserAccessTokenDomain::FCollectJoinedGuildsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Guild::Model::FJoinedGuildPtr>>, public TSharedFromThis<FCollectJoinedGuildsTask>
    {
        const TSharedPtr<FUserAccessTokenDomain> Self;
        const TFunction<void(TArray<Gs2::Guild::Model::FJoinedGuildPtr>)> OnCollected;
    const TOptional<FString> QueryGuildModelName;
    public:
        explicit FCollectJoinedGuildsTask(const TSharedPtr<FUserAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Guild::Model::FJoinedGuildPtr>)> OnCollected,const TOptional<FString> GuildModelName) : Self(Self), OnCollected(OnCollected), QueryGuildModelName(GuildModelName) {}
        FCollectJoinedGuildsTask(const FCollectJoinedGuildsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryGuildModelName(From.QueryGuildModelName) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Guild::Model::FJoinedGuildPtr>>> Result) override
        {
            TArray<Gs2::Guild::Model::FJoinedGuildPtr> Items;
            auto Iterator = Self->JoinedGuilds(QueryGuildModelName)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Guild::Model::FJoinedGuildPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeJoinedGuilds(
        TFunction<void(TArray<Gs2::Guild::Model::FJoinedGuildPtr>)> Callback,const TOptional<FString> GuildModelName
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Guild::Domain::FGs2GuildDomain> WeakService = this->Service;
        const auto SourceToken = this->AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid() ? TOptional<FString>(SourceToken->GetUserId()) : TOptional<FString>();
        const int32 RegisteredTimeOffset = SourceToken.IsValid() ? SourceToken->GetTimeOffset().Get(0) : 0;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryGuildModelName = GuildModelName;
        const auto Parent = Gs2::Guild::Model::Cache::FJoinedGuildCache::CreateCacheParentKey(
        NamespaceName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Guild::Model::FJoinedGuild::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Guild::Model::FJoinedGuildPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Guild::Model::FJoinedGuild>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryGuildModelName, SourceToken, RegisteredUserId, RegisteredTimeOffset]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid() || !SourceToken.IsValid() || !RegisteredUserId.IsSet()) return;
                const auto TokenSnapshot = MakeShared<Gs2::Auth::Model::FAccessToken>(*SourceToken);
                if (TokenSnapshot->GetUserId() != RegisteredUserId || TokenSnapshot->GetTimeOffset().Get(0) != RegisteredTimeOffset) return;
                const auto Domain = MakeShared<FUserAccessTokenDomain>(Owner, WeakService.Pin(), QueryNamespaceName, TokenSnapshot);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectJoinedGuildsTask>>(Domain, Callback, QueryGuildModelName);
                Task->StartBackgroundTask();
            }
        );
    }

    void FUserAccessTokenDomain::InvalidateJoinedGuilds(const TOptional<FString> GuildModelName)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Guild::Model::FJoinedGuild::TypeName,
            Gs2::Guild::Model::Cache::FJoinedGuildCache::CreateCacheParentKey(
        NamespaceName,
        AccessToken.IsValid() ? AccessToken->GetUserId() : TOptional<FString>(),
        AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
    )
        );
    }

    FUserAccessTokenDomain::FSubscribeJoinedGuildsWithInitialCallTask::FSubscribeJoinedGuildsWithInitialCallTask(const TSharedPtr<FUserAccessTokenDomain>& Self, TFunction<void(TArray<Gs2::Guild::Model::FJoinedGuildPtr>)> Callback,const TOptional<FString> GuildModelName) : Self(Self), Callback(Callback), QueryGuildModelName(GuildModelName) {}
    FUserAccessTokenDomain::FSubscribeJoinedGuildsWithInitialCallTask::FSubscribeJoinedGuildsWithInitialCallTask(const FSubscribeJoinedGuildsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryGuildModelName(From.QueryGuildModelName) {}
    Gs2::Core::Model::FGs2ErrorPtr FUserAccessTokenDomain::FSubscribeJoinedGuildsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectJoinedGuildsTask>>(Self, TFunction<void(TArray<Gs2::Guild::Model::FJoinedGuildPtr>)>(), QueryGuildModelName);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeJoinedGuilds(Callback, QueryGuildModelName);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FUserAccessTokenDomain::FSubscribeJoinedGuildsWithInitialCallTask>> FUserAccessTokenDomain::SubscribeJoinedGuildsWithInitialCall(TFunction<void(TArray<Gs2::Guild::Model::FJoinedGuildPtr>)> Callback,const TOptional<FString> GuildModelName)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeJoinedGuildsWithInitialCallTask>>(this->AsShared(), Callback, GuildModelName);
    }

    TSharedPtr<Gs2::Guild::Domain::Model::FJoinedGuildAccessTokenDomain> FUserAccessTokenDomain::JoinedGuild(
        const FString GuildModelName,
        const FString GuildName
    )
    {
        return MakeShared<Gs2::Guild::Domain::Model::FJoinedGuildAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            GuildModelName == TEXT("") ? TOptional<FString>() : TOptional<FString>(GuildModelName),
            GuildName == TEXT("") ? TOptional<FString>() : TOptional<FString>(GuildName)
        );
    }

    FString FUserAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            ChildType;
    }

    FString FUserAccessTokenDomain::CreateCacheKey(
        TOptional<FString> UserId
    )
    {
        return FString("") +
            (UserId.IsSet() ? *UserId : "null");
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
