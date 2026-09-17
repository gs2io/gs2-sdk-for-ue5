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

#include "Guild/Domain/Model/SendMemberRequestAccessToken.h"
#include "Guild/Domain/Model/SendMemberRequest.h"
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


#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Guild::Domain::Model
{

    FSendMemberRequestAccessTokenDomain::FSendMemberRequestAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Guild::Domain::FGs2GuildDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<FString> GuildModelName,
        const TOptional<FString> GuildName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Guild::FGs2GuildRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        GuildModelName(GuildModelName),
        GuildName(GuildName),
        ParentKey(Gs2::Guild::Model::Cache::FSendMemberRequestCache::CreateCacheParentKey(

            NamespaceName,
            GuildModelName,

            UserId(),
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()

        ))
    {
    }

    FSendMemberRequestAccessTokenDomain::FSendMemberRequestAccessTokenDomain(
        const FSendMemberRequestAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        GuildModelName(From.GuildModelName),
        GuildName(From.GuildName),
        ParentKey(From.ParentKey)
    {

    }

    FSendMemberRequestAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FSendMemberRequestAccessTokenDomain>& Self,
        const Request::FGetSendRequestRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSendMemberRequestAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSendMemberRequestAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Model::FSendMemberRequest>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithGuildModelName(Self->GuildModelName)
            ->WithTargetGuildName(Self->GuildName);
        const auto Future = Self->Client->GetSendRequest(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel.IsValid() && ResultModel->GetItem().IsValid())
        {
            Gs2::Guild::Model::Cache::FSendMemberRequestCache::Put(
                Self->Gs2->Cache,
                Request->GetNamespaceName(), Self->UserId(), Request->GetGuildModelName(),
                Request->GetTargetGuildName(), Self->AccessToken->GetTimeOffset(), ResultModel->GetItem()
            );
        }
        *Result = ResultModel.IsValid() ? ResultModel->GetItem() : nullptr;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSendMemberRequestAccessTokenDomain::FGetTask>> FSendMemberRequestAccessTokenDomain::Get(
        Request::FGetSendRequestRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FSendMemberRequestAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> GuildModelName,
        TOptional<FString> GuildName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (GuildModelName.IsSet() ? *GuildModelName : "null") + ":" +
            (GuildName.IsSet() ? *GuildName : "null") + ":" +
            ChildType;
    }

    FString FSendMemberRequestAccessTokenDomain::CreateCacheKey(
        TOptional<FString> GuildModelName,
        TOptional<FString> GuildName
    )
    {
        return FString("") +
            (GuildModelName.IsSet() ? *GuildModelName : "null") + ":" + 
            (GuildName.IsSet() ? *GuildName : "null");
    }

    FSendMemberRequestAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FSendMemberRequestAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FSendMemberRequestAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FSendMemberRequestAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Model::FSendMemberRequest>> Result
    )
    {
        const FString CacheKey = Gs2::Guild::Model::Cache::FSendMemberRequestCache::CreateCacheKey(Self->GuildName);

        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Guild::Model::FSendMemberRequest::TypeName,
            Self->ParentKey,
            CacheKey,
            [this, Result, CacheKey]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                // ReSharper disable once CppLocalVariableMayBeConst
                TSharedPtr<Gs2::Guild::Model::FSendMemberRequest> Value;
                auto bCacheHit = Gs2::Guild::Model::Cache::FSendMemberRequestCache::TryGet(

                    Self->Gs2->Cache, Self->NamespaceName, Self->UserId(), Self->GuildModelName, Self->GuildName,

                    Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>(), &Value

                );
                if (!bCacheHit) {
                    const auto Future = Self->Get(
                        MakeShared<Gs2::Guild::Request::FGetSendRequestRequest>()
                    );
                    Future->StartSynchronousTask();
                    if (Future->GetTask().IsError())
                    {
                        const auto Error = Future->GetTask().Error();
                        if (!Error.IsValid() || Error->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                        {
                            return Error;
                        }
                        Gs2::Guild::Model::Cache::FSendMemberRequestCache::Put(

                            Self->Gs2->Cache, Self->NamespaceName, Self->UserId(), Self->GuildModelName, Self->GuildName,

                            Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>(), nullptr

                        );

                        if (!Error->GetErrors().IsValid() || Error->Count() == 0 || !Error->Detail(0).IsValid() || Error->Detail(0)->GetComponent() != "sendMemberRequest")
                        {
                            return Error;
                        }
                    }
                    else
                    {
                        Value = Future->GetTask().Result();
                    }
                    Future->EnsureCompletion();
                }
                if (!bCacheHit)
                {
                    Gs2::Guild::Model::FSendMemberRequestPtr ExistingObject;

                    const bool Existing = Gs2::Guild::Model::Cache::FSendMemberRequestCache::TryGet(

                        Self->Gs2->Cache, Self->NamespaceName, Self->UserId(), Self->GuildModelName, Self->GuildName,

                        Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>(), &ExistingObject

                    );
                    if (!Existing || ExistingObject != Value)
                    {
                        Gs2::Guild::Model::Cache::FSendMemberRequestCache::Put(

                            Self->Gs2->Cache, Self->NamespaceName, Self->UserId(), Self->GuildModelName, Self->GuildName,

                            Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>(), Value

                        );
                    }
                }

                *Result = Value;

                return nullptr;
            }
        );
    }

    TSharedPtr<FAsyncTask<FSendMemberRequestAccessTokenDomain::FModelTask>> FSendMemberRequestAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FSendMemberRequestAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FSendMemberRequestAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Guild::Model::FSendMemberRequestPtr)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Guild::Domain::FGs2GuildDomain> WeakService = Service;
        const FString RegisteredParentKey = ParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryGuildModelName = GuildModelName;
        const TOptional<FString> QueryGuildName = GuildName;
        const auto SourceToken = AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid()
            ? TOptional<FString>(SourceToken->GetUserId())
            : TOptional<FString>();
        const int32 RegisteredTimeOffset = SourceToken.IsValid() ? SourceToken->GetTimeOffset().Get(0) : 0;

        return Gs2->Cache->Subscribe(
            Gs2::Guild::Model::FSendMemberRequest::TypeName,
            ParentKey,
            Gs2::Guild::Model::Cache::FSendMemberRequestCache::CreateCacheKey(GuildName),

            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Guild::Model::FSendMemberRequest>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryGuildModelName, QueryGuildName, SourceToken, RegisteredUserId, RegisteredTimeOffset]()

            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid() || !SourceToken.IsValid() || !RegisteredUserId.IsSet())
                {
                    return;
                }
                const auto TokenSnapshot = MakeShared<Gs2::Auth::Model::FAccessToken>(*SourceToken);
                if (TokenSnapshot->GetUserId() != RegisteredUserId || TokenSnapshot->GetTimeOffset().Get(0) != RegisteredTimeOffset)

                {
                    return;
                }
                const auto Domain = MakeShared<FSendMemberRequestAccessTokenDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    TokenSnapshot,
                    QueryGuildModelName,
                    QueryGuildName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FSendMemberRequestAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Guild::Model::FSendMemberRequest::TypeName,
            ParentKey,
            Gs2::Guild::Model::Cache::FSendMemberRequestCache::CreateCacheKey(GuildName),

            CallbackID
        );
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
