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
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Guild::Domain::Model
{

    FUserDomain::FUserDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Guild::Domain::FGs2GuildDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Guild::FGs2GuildRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        ParentKey(Gs2::Guild::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "User"
        ))
    {
    }

    FUserDomain::FUserDomain(
        const FUserDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        ParentKey(From.ParentKey)
    {

    }

    FUserDomain::FCreateGuildTask::FCreateGuildTask(
        const TSharedPtr<FUserDomain>& Self,
        const Request::FCreateGuildByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FCreateGuildTask::FCreateGuildTask(
        const FCreateGuildTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FCreateGuildTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FGuildDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->CreateGuildByUserId(
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

    TSharedPtr<FAsyncTask<FUserDomain::FCreateGuildTask>> FUserDomain::CreateGuild(
        Request::FCreateGuildByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateGuildTask>>(this->AsShared(), Request);
    }

    FUserDomain::FAssumeTask::FAssumeTask(
        const TSharedPtr<FUserDomain>& Self,
        const Request::FAssumeByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FAssumeTask::FAssumeTask(
        const FAssumeTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FAssumeTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Auth::Domain::Model::FAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->AssumeByUserId(
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

    TSharedPtr<FAsyncTask<FUserDomain::FAssumeTask>> FUserDomain::Assume(
        Request::FAssumeByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FAssumeTask>>(this->AsShared(), Request);
    }

    FUserDomain::FSendRequestTask::FSendRequestTask(
        const TSharedPtr<FUserDomain>& Self,
        const Request::FSendRequestByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FSendRequestTask::FSendRequestTask(
        const FSendRequestTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FSendRequestTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FGuildDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->SendRequestByUserId(
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

                    Self->Gs2->Cache, Self->NamespaceName, Self->UserId, RequestModel->GetGuildModelName(),

                    ResultModel->GetSendMemberRequest()->GetTargetGuildName(), TOptional<int32>(), ResultModel->GetSendMemberRequest()

                );
            }
        }
        auto Domain = MakeShared<Gs2::Guild::Domain::Model::FGuildDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            Request->GetGuildModelName(),
            Request->GetTargetGuildName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FSendRequestTask>> FUserDomain::SendRequest(
        Request::FSendRequestByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FSendRequestTask>>(this->AsShared(), Request);
    }

    FUserDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FUserDomain>& Self,
        const Request::FDeleteRequestByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FSendMemberRequestDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->DeleteRequestByUserId(
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

                    Self->Gs2->Cache, Self->NamespaceName, Self->UserId, RequestModel->GetGuildModelName(),

                    RequestModel->GetTargetGuildName(), TOptional<int32>()

                );
            }
        }
        auto Domain = MakeShared<Gs2::Guild::Domain::Model::FSendMemberRequestDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetUserId(),
            Request->GetGuildModelName(),
            Request->GetTargetGuildName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FDeleteTask>> FUserDomain::Delete(
        Request::FDeleteRequestByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    Gs2::Guild::Domain::Iterator::FDescribeSendRequestsByUserIdIteratorPtr FUserDomain::SendRequests(
        const FString GuildModelName,
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Guild::Domain::Iterator::FDescribeSendRequestsByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            UserId,
            GuildModelName,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeSendRequests(

        TFunction<void()> Callback,

        const FString GuildModelName

    )

    {

        return Gs2::Guild::Model::Cache::FSendMemberRequestCache::ListSubscribe(

            Gs2->Cache, NamespaceName, GuildModelName, UserId, TOptional<int32>(),

            [Callback](const TArray<Gs2::Guild::Model::FSendMemberRequestPtr>&) { Callback(); }

        );

    }



    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeSendRequests(
        const FString GuildModelName,
        TFunction<void()> Callback
    )
    {
        return SubscribeSendRequests(Callback, GuildModelName);

    }

    void FUserDomain::UnsubscribeSendRequests(
        const FString GuildModelName,
        Gs2::Core::Domain::CallbackID CallbackID,

        const TOptional<FString> TimeOffsetToken

    )
    {
        Gs2::Guild::Model::Cache::FSendMemberRequestCache::ListUnsubscribe(

            Gs2->Cache, NamespaceName, GuildModelName, UserId, TOptional<int32>(), CallbackID

        );

    }



    class FUserDomain::FCollectSendRequestsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Guild::Model::FSendMemberRequestPtr>>, public TSharedFromThis<FCollectSendRequestsTask>

    {

        const TSharedPtr<FUserDomain> Self;

        const TFunction<void(TArray<Gs2::Guild::Model::FSendMemberRequestPtr>)> OnCollected;

        const FString QueryGuildModelName;

        const TOptional<FString> QueryTimeOffsetToken;

    public:

        FCollectSendRequestsTask(const TSharedPtr<FUserDomain>& Self, TFunction<void(TArray<Gs2::Guild::Model::FSendMemberRequestPtr>)> OnCollected, const FString GuildModelName, const TOptional<FString> TimeOffsetToken): Self(Self), OnCollected(OnCollected), QueryGuildModelName(GuildModelName), QueryTimeOffsetToken(TimeOffsetToken) {}

        FCollectSendRequestsTask(const FCollectSendRequestsTask& From): TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryGuildModelName(From.QueryGuildModelName), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}

        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Guild::Model::FSendMemberRequestPtr>>> Result) override

        {

            TArray<Gs2::Guild::Model::FSendMemberRequestPtr> Items;

            auto Iterator = Self->SendRequests(QueryGuildModelName, QueryTimeOffsetToken)->begin();

            while (Iterator.HasNext()) { if (Iterator.IsError()) return Iterator.Error(); if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current()); ++Iterator; }

            if (Iterator.IsError()) return Iterator.Error();

            *Result = MakeShared<TArray<Gs2::Guild::Model::FSendMemberRequestPtr>>(Items);

            if (OnCollected) OnCollected(Items);

            return nullptr;

        }

    };



    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeSendRequests(

        TFunction<void(TArray<Gs2::Guild::Model::FSendMemberRequestPtr>)> Callback,

        const FString GuildModelName,

        const TOptional<FString> TimeOffsetToken

    )

    {

        const auto Parent = Gs2::Guild::Model::Cache::FSendMemberRequestCache::CreateCacheParentKey(NamespaceName, GuildModelName, UserId, TOptional<int32>());

        const auto WeakGs2 = this->Gs2;

        const auto WeakService = this->Service;

        const auto QueryNamespaceName = this->NamespaceName;

        const auto QueryUserId = this->UserId;

        return Gs2->Cache->ListSubscribeTyped(

            Gs2::Guild::Model::FSendMemberRequest::TypeName, Parent,

            [Callback](const TArray<FGs2ObjectPtr>& Values) { TArray<Gs2::Guild::Model::FSendMemberRequestPtr> Items; for (const auto& Value : Values) if (Value.IsValid()) Items.Add(StaticCastSharedPtr<Gs2::Guild::Model::FSendMemberRequest>(Value)); Callback(Items); },

            [WeakGs2, WeakService, Callback, GuildModelName, TimeOffsetToken, QueryNamespaceName, QueryUserId]() { const auto Domain = MakeShared<FUserDomain>(WeakGs2, WeakService, QueryNamespaceName, QueryUserId); const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectSendRequestsTask>>(Domain, Callback, GuildModelName, TimeOffsetToken); Task->StartBackgroundTask(); }

        );
    }

    void FUserDomain::InvalidateSendRequests(const FString GuildModelName, const TOptional<FString> TimeOffsetToken)

    {

        Gs2->Cache->ClearListCache(Gs2::Guild::Model::FSendMemberRequest::TypeName, Gs2::Guild::Model::Cache::FSendMemberRequestCache::CreateCacheParentKey(NamespaceName, GuildModelName, UserId, TOptional<int32>()));

    }



    FUserDomain::FSubscribeSendRequestsWithInitialCallTask::FSubscribeSendRequestsWithInitialCallTask(const TSharedPtr<FUserDomain>& Self, TFunction<void(TArray<Gs2::Guild::Model::FSendMemberRequestPtr>)> Callback, const FString GuildModelName, const TOptional<FString> TimeOffsetToken): Self(Self), Callback(Callback), QueryGuildModelName(GuildModelName), QueryTimeOffsetToken(TimeOffsetToken) {}

    FUserDomain::FSubscribeSendRequestsWithInitialCallTask::FSubscribeSendRequestsWithInitialCallTask(const FSubscribeSendRequestsWithInitialCallTask& From): TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryGuildModelName(From.QueryGuildModelName), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FSubscribeSendRequestsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)

    {

        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectSendRequestsTask>>(Self, TFunction<void(TArray<Gs2::Guild::Model::FSendMemberRequestPtr>)>(), QueryGuildModelName, QueryTimeOffsetToken); Task->StartSynchronousTask(); Task->EnsureCompletion(); if (Task->GetTask().IsError()) return Task->GetTask().Error(); const auto Values = Task->GetTask().Result(); const auto CallbackId = Self->SubscribeSendRequests(Callback, QueryGuildModelName, QueryTimeOffsetToken); Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId); return nullptr;

    }

    TSharedPtr<FAsyncTask<FUserDomain::FSubscribeSendRequestsWithInitialCallTask>> FUserDomain::SubscribeSendRequestsWithInitialCall(TFunction<void(TArray<Gs2::Guild::Model::FSendMemberRequestPtr>)> Callback, const FString GuildModelName, const TOptional<FString> TimeOffsetToken)

    {

        return Gs2::Core::Util::New<FAsyncTask<FSubscribeSendRequestsWithInitialCallTask>>(this->AsShared(), Callback, GuildModelName, TimeOffsetToken);

    }



    TSharedPtr<Gs2::Guild::Domain::Model::FSendMemberRequestDomain> FUserDomain::SendMemberRequest(
        const FString GuildModelName,
        const FString GuildName
    )
    {
        return MakeShared<Gs2::Guild::Domain::Model::FSendMemberRequestDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            GuildModelName == TEXT("") ? TOptional<FString>() : TOptional<FString>(GuildModelName),
            GuildName == TEXT("") ? TOptional<FString>() : TOptional<FString>(GuildName)
        );
    }

    Gs2::Guild::Domain::Iterator::FSearchGuildsByUserIdIteratorPtr FUserDomain::SearchGuilds(
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
        return MakeShared<Gs2::Guild::Domain::Iterator::FSearchGuildsByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            GuildModelName,
            UserId,
            DisplayName,
            Attributes1,
            Attributes2,
            Attributes3,
            Attributes4,
            Attributes5,
            JoinPolicies,
            IncludeFullMembersGuild,
            TOptional<FString>(),
            TimeOffsetToken
        );
    }

    Gs2::Guild::Domain::Iterator::FDescribeJoinedGuildsByUserIdIteratorPtr FUserDomain::JoinedGuilds(
        const TOptional<FString> GuildModelName,
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Guild::Domain::Iterator::FDescribeJoinedGuildsByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            UserId,
            GuildModelName,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeJoinedGuilds(
    TFunction<void()> Callback
        , const TOptional<FString> GuildModelName
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Guild::Model::FJoinedGuild::TypeName,
            Gs2::Guild::Model::Cache::FJoinedGuildCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FUserDomain::UnsubscribeJoinedGuilds(

        Gs2::Core::Domain::CallbackID CallbackID, const TOptional<FString> GuildModelName, const TOptional<FString> TimeOffsetToken
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Guild::Model::FJoinedGuild::TypeName,
            Gs2::Guild::Model::Cache::FJoinedGuildCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FUserDomain::FCollectJoinedGuildsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Guild::Model::FJoinedGuildPtr>>, public TSharedFromThis<FCollectJoinedGuildsTask>
    {
        const TSharedPtr<FUserDomain> Self;
        const TFunction<void(TArray<Gs2::Guild::Model::FJoinedGuildPtr>)> OnCollected;
    const TOptional<FString> QueryGuildModelName;const TOptional<FString> QueryTimeOffsetToken;
    public:
        explicit FCollectJoinedGuildsTask(const TSharedPtr<FUserDomain>& Self, TFunction<void(TArray<Gs2::Guild::Model::FJoinedGuildPtr>)> OnCollected,const TOptional<FString> GuildModelName,const TOptional<FString> TimeOffsetToken) : Self(Self), OnCollected(OnCollected), QueryGuildModelName(GuildModelName), QueryTimeOffsetToken(TimeOffsetToken) {}
        FCollectJoinedGuildsTask(const FCollectJoinedGuildsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryGuildModelName(From.QueryGuildModelName), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Guild::Model::FJoinedGuildPtr>>> Result) override
        {
            TArray<Gs2::Guild::Model::FJoinedGuildPtr> Items;
            auto Iterator = Self->JoinedGuilds(QueryGuildModelName, QueryTimeOffsetToken)->begin();
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

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeJoinedGuilds(
        TFunction<void(TArray<Gs2::Guild::Model::FJoinedGuildPtr>)> Callback,const TOptional<FString> GuildModelName,const TOptional<FString> TimeOffsetToken
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Guild::Domain::FGs2GuildDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryUserId = UserId;
        const auto QueryGuildModelName = GuildModelName;
        const auto QueryTimeOffsetToken = TimeOffsetToken;
        const auto Parent = Gs2::Guild::Model::Cache::FJoinedGuildCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        TOptional<int32>()
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
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryUserId, QueryGuildModelName, QueryTimeOffsetToken]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FUserDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryUserId);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectJoinedGuildsTask>>(Domain, Callback, QueryGuildModelName, QueryTimeOffsetToken);
                Task->StartBackgroundTask();
            }
        );
    }

    void FUserDomain::InvalidateJoinedGuilds(const TOptional<FString> GuildModelName,const TOptional<FString> TimeOffsetToken)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Guild::Model::FJoinedGuild::TypeName,
            Gs2::Guild::Model::Cache::FJoinedGuildCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        TOptional<int32>()
    )
        );
    }

    FUserDomain::FSubscribeJoinedGuildsWithInitialCallTask::FSubscribeJoinedGuildsWithInitialCallTask(const TSharedPtr<FUserDomain>& Self, TFunction<void(TArray<Gs2::Guild::Model::FJoinedGuildPtr>)> Callback,const TOptional<FString> GuildModelName,const TOptional<FString> TimeOffsetToken) : Self(Self), Callback(Callback), QueryGuildModelName(GuildModelName), QueryTimeOffsetToken(TimeOffsetToken) {}
    FUserDomain::FSubscribeJoinedGuildsWithInitialCallTask::FSubscribeJoinedGuildsWithInitialCallTask(const FSubscribeJoinedGuildsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryGuildModelName(From.QueryGuildModelName), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FSubscribeJoinedGuildsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectJoinedGuildsTask>>(Self, TFunction<void(TArray<Gs2::Guild::Model::FJoinedGuildPtr>)>(), QueryGuildModelName, QueryTimeOffsetToken);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeJoinedGuilds(Callback, QueryGuildModelName, QueryTimeOffsetToken);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FUserDomain::FSubscribeJoinedGuildsWithInitialCallTask>> FUserDomain::SubscribeJoinedGuildsWithInitialCall(TFunction<void(TArray<Gs2::Guild::Model::FJoinedGuildPtr>)> Callback,const TOptional<FString> GuildModelName,const TOptional<FString> TimeOffsetToken)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeJoinedGuildsWithInitialCallTask>>(this->AsShared(), Callback, GuildModelName, TimeOffsetToken);
    }

    TSharedPtr<Gs2::Guild::Domain::Model::FJoinedGuildDomain> FUserDomain::JoinedGuild(
        const FString GuildModelName,
        const FString GuildName
    )
    {
        return MakeShared<Gs2::Guild::Domain::Model::FJoinedGuildDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            GuildModelName == TEXT("") ? TOptional<FString>() : TOptional<FString>(GuildModelName),
            GuildName == TEXT("") ? TOptional<FString>() : TOptional<FString>(GuildName)
        );
    }

    FString FUserDomain::CreateCacheParentKey(
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

    FString FUserDomain::CreateCacheKey(
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
