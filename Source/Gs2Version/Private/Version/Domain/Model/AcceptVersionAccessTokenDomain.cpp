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

#include "Version/Domain/Model/AcceptVersionAccessToken.h"
#include "Version/Model/Cache/AcceptVersion.h"
#include "Version/Domain/Model/AcceptVersion.h"
#include "Version/Domain/Model/Namespace.h"
#include "Version/Domain/Model/VersionModelMaster.h"
#include "Version/Domain/Model/VersionModel.h"
#include "Version/Domain/Model/AcceptVersion.h"
#include "Version/Domain/Model/AcceptVersionAccessToken.h"
#include "Version/Domain/Model/Checker.h"
#include "Version/Domain/Model/CheckerAccessToken.h"
#include "Version/Domain/Model/User.h"
#include "Version/Domain/Model/UserAccessToken.h"
#include "Version/Domain/Model/CurrentVersionMaster.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Version::Domain::Model
{

    FAcceptVersionAccessTokenDomain::FAcceptVersionAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Version::Domain::FGs2VersionDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<FString> VersionName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Version::FGs2VersionRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        VersionName(VersionName)
    {
    }

    FAcceptVersionAccessTokenDomain::FAcceptVersionAccessTokenDomain(
        const FAcceptVersionAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        VersionName(From.VersionName)
    {

    }

    FAcceptVersionAccessTokenDomain::FAcceptTask::FAcceptTask(
        const TSharedPtr<FAcceptVersionAccessTokenDomain>& Self,
        const Request::FAcceptRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FAcceptVersionAccessTokenDomain::FAcceptTask::FAcceptTask(
        const FAcceptTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FAcceptVersionAccessTokenDomain::FAcceptTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Version::Domain::Model::FAcceptVersionAccessTokenDomain>> Result
    )
    {
        const auto SourceToken = Self->AccessToken;
        Gs2::Auth::Model::FAccessTokenPtr TokenSnapshot;
        if (SourceToken.IsValid())
        {
            TokenSnapshot = MakeShared<Gs2::Auth::Model::FAccessToken>(*SourceToken);
        }
        const auto SnapshotUserId = TokenSnapshot.IsValid()
            ? TokenSnapshot->GetUserId()
            : TOptional<FString>();
        const auto SnapshotTimeOffset = TokenSnapshot.IsValid()
            ? TokenSnapshot->GetTimeOffset()
            : TOptional<int32>();
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithVersionName(Self->VersionName)
            ->WithAccessToken(TokenSnapshot.IsValid() ? TokenSnapshot->GetToken() : TOptional<FString>());
        const auto Future = Self->Client->Accept(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
        {
            const auto Item = ResultModel->GetItem();
            Gs2::Version::Model::Cache::FAcceptVersionCache::Put(
                Self->Gs2->Cache,
                Request->GetNamespaceName(),
                SnapshotUserId,
                Item->GetVersionName(),
                SnapshotTimeOffset,
                Item
            );
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAcceptVersionAccessTokenDomain::FAcceptTask>> FAcceptVersionAccessTokenDomain::Accept(
        Request::FAcceptRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FAcceptTask>>(this->AsShared(), Request);
    }

    FAcceptVersionAccessTokenDomain::FRejectTask::FRejectTask(
        const TSharedPtr<FAcceptVersionAccessTokenDomain>& Self,
        const Request::FRejectRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FAcceptVersionAccessTokenDomain::FRejectTask::FRejectTask(
        const FRejectTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FAcceptVersionAccessTokenDomain::FRejectTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Version::Domain::Model::FAcceptVersionAccessTokenDomain>> Result
    )
    {
        const auto SourceToken = Self->AccessToken;
        Gs2::Auth::Model::FAccessTokenPtr TokenSnapshot;
        if (SourceToken.IsValid())
        {
            TokenSnapshot = MakeShared<Gs2::Auth::Model::FAccessToken>(*SourceToken);
        }
        const auto SnapshotUserId = TokenSnapshot.IsValid()
            ? TokenSnapshot->GetUserId()
            : TOptional<FString>();
        const auto SnapshotTimeOffset = TokenSnapshot.IsValid()
            ? TokenSnapshot->GetTimeOffset()
            : TOptional<int32>();
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithVersionName(Self->VersionName)
            ->WithAccessToken(TokenSnapshot.IsValid() ? TokenSnapshot->GetToken() : TOptional<FString>());
        const auto Future = Self->Client->Reject(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
        {
            const auto Item = ResultModel->GetItem();
            Gs2::Version::Model::Cache::FAcceptVersionCache::Put(
                Self->Gs2->Cache,
                Request->GetNamespaceName(),
                SnapshotUserId,
                Item->GetVersionName(),
                SnapshotTimeOffset,
                Item
            );
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAcceptVersionAccessTokenDomain::FRejectTask>> FAcceptVersionAccessTokenDomain::Reject(
        Request::FRejectRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FRejectTask>>(this->AsShared(), Request);
    }

    FAcceptVersionAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FAcceptVersionAccessTokenDomain>& Self,
        const Request::FGetAcceptVersionRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FAcceptVersionAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FAcceptVersionAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Version::Model::FAcceptVersion>> Result
    )
    {
        const auto SourceToken = Self->AccessToken;
        Gs2::Auth::Model::FAccessTokenPtr TokenSnapshot;
        if (SourceToken.IsValid())
        {
            TokenSnapshot = MakeShared<Gs2::Auth::Model::FAccessToken>(*SourceToken);
        }
        const auto SnapshotUserId = TokenSnapshot.IsValid()
            ? TokenSnapshot->GetUserId()
            : TOptional<FString>();
        const auto SnapshotTimeOffset = TokenSnapshot.IsValid()
            ? TokenSnapshot->GetTimeOffset()
            : TOptional<int32>();
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(TokenSnapshot.IsValid() ? TokenSnapshot->GetToken() : TOptional<FString>())
            ->WithVersionName(Self->VersionName);
        const auto Future = Self->Client->GetAcceptVersion(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
        {
            const auto Item = ResultModel->GetItem();
            Gs2::Version::Model::Cache::FAcceptVersionCache::Put(
                Self->Gs2->Cache,
                Request->GetNamespaceName(),
                SnapshotUserId,
                Item->GetVersionName(),
                SnapshotTimeOffset,
                Item
            );
        }
        *Result = ResultModel.IsValid() ? ResultModel->GetItem() : nullptr;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAcceptVersionAccessTokenDomain::FGetTask>> FAcceptVersionAccessTokenDomain::Get(
        Request::FGetAcceptVersionRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FAcceptVersionAccessTokenDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FAcceptVersionAccessTokenDomain>& Self,
        const Request::FDeleteAcceptVersionRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FAcceptVersionAccessTokenDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FAcceptVersionAccessTokenDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Version::Domain::Model::FAcceptVersionAccessTokenDomain>> Result
    )
    {
        const auto SourceToken = Self->AccessToken;
        Gs2::Auth::Model::FAccessTokenPtr TokenSnapshot;
        if (SourceToken.IsValid())
        {
            TokenSnapshot = MakeShared<Gs2::Auth::Model::FAccessToken>(*SourceToken);
        }
        const auto SnapshotUserId = TokenSnapshot.IsValid()
            ? TokenSnapshot->GetUserId()
            : TOptional<FString>();
        const auto SnapshotTimeOffset = TokenSnapshot.IsValid()
            ? TokenSnapshot->GetTimeOffset()
            : TOptional<int32>();
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(TokenSnapshot.IsValid() ? TokenSnapshot->GetToken() : TOptional<FString>())
            ->WithVersionName(Self->VersionName);
        const auto Future = Self->Client->DeleteAcceptVersion(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            const auto Error = Future->GetTask().Error();
            if (!Error.IsValid() || !Error->IsChildOf(Gs2::Core::Model::FNotFoundError::Class))
            {
                return Error;
            }
            *Result = Self;
            return nullptr;
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
        {
            Gs2::Version::Model::Cache::FAcceptVersionCache::Delete(
                Self->Gs2->Cache,
                Request->GetNamespaceName(),
                SnapshotUserId,
                ResultModel->GetItem()->GetVersionName(),
                SnapshotTimeOffset
            );
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAcceptVersionAccessTokenDomain::FDeleteTask>> FAcceptVersionAccessTokenDomain::Delete(
        Request::FDeleteAcceptVersionRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FAcceptVersionAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> VersionName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (VersionName.IsSet() ? *VersionName : "null") + ":" +
            ChildType;
    }

    FString FAcceptVersionAccessTokenDomain::CreateCacheKey(
        TOptional<FString> VersionName
    )
    {
        return FString("") +
            (VersionName.IsSet() ? *VersionName : "null");
    }

    FAcceptVersionAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FAcceptVersionAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FAcceptVersionAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FAcceptVersionAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Version::Model::FAcceptVersion>> Result
    )
    {
        const auto SourceToken = Self->AccessToken;
        Gs2::Auth::Model::FAccessTokenPtr TokenSnapshot;
        if (SourceToken.IsValid())
        {
            TokenSnapshot = MakeShared<Gs2::Auth::Model::FAccessToken>(*SourceToken);
        }
        const auto OwnerUserId = TokenSnapshot.IsValid()
            ? TokenSnapshot->GetUserId()
            : TOptional<FString>();
        const auto OwnerTimeOffset = TokenSnapshot.IsValid()
            ? TokenSnapshot->GetTimeOffset()
            : TOptional<int32>();
        const auto ParentKey = Gs2::Version::Model::Cache::FAcceptVersionCache::CreateCacheParentKey(
            Self->NamespaceName,
            OwnerUserId,
            OwnerTimeOffset
        );
        const auto CacheKey = Gs2::Version::Model::Cache::FAcceptVersionCache::CreateCacheKey(Self->VersionName);
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Version::Model::FAcceptVersion::TypeName,
            ParentKey,
            CacheKey,
            [this, Result, OwnerUserId, OwnerTimeOffset, TokenSnapshot]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Version::Model::FAcceptVersionPtr Value;
                if (Gs2::Version::Model::Cache::FAcceptVersionCache::TryGet(
                    Self->Gs2->Cache,
                    Self->NamespaceName,
                    OwnerUserId,
                    Self->VersionName,
                    OwnerTimeOffset,
                    &Value
                ))
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto FetchDomain = MakeShared<FAcceptVersionAccessTokenDomain>(
                    Self->Gs2,
                    Self->Service,
                    Self->NamespaceName,
                    TokenSnapshot,
                    Self->VersionName
                );
                const auto Error = Gs2::Version::Model::Cache::FAcceptVersionCache::Fetch(
                    Self->Gs2->Cache,
                    Self->NamespaceName,
                    OwnerUserId,
                    Self->VersionName,
                    OwnerTimeOffset,
                    [TaskSelf = FetchDomain](Gs2::Version::Model::FAcceptVersionPtr* OutValue) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = TaskSelf->Get(MakeShared<Gs2::Version::Request::FGetAcceptVersionRequest>());
                        Future->StartSynchronousTask();
                        if (Future->GetTask().IsError())
                        {
                            return Future->GetTask().Error();
                        }
                        *OutValue = Future->GetTask().Result();
                        Future->EnsureCompletion();
                        return nullptr;
                    },
                    &Value
                );
                if (Error.IsValid())
                {
                    return Error;
                }
                *Result = Value;
                return nullptr;
            }
        );
    }

    TSharedPtr<FAsyncTask<FAcceptVersionAccessTokenDomain::FModelTask>> FAcceptVersionAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FAcceptVersionAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    FAcceptVersionAccessTokenDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FAcceptVersionAccessTokenDomain> Self,
        const TFunction<void(Gs2::Version::Model::FAcceptVersionPtr)>& Callback
    ): Self(Self), Callback(Callback)
    {
    }

    FAcceptVersionAccessTokenDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ): TGs2Future(From), Self(From.Self), Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FAcceptVersionAccessTokenDomain::FSubscribeWithInitialCallTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result
    )
    {
        const auto Future = Self->Model();
        Future->StartSynchronousTask();
        Future->EnsureCompletion();
        if (Future->GetTask().IsError()) return Future->GetTask().Error();
        const auto Item = Future->GetTask().Result();
        const auto ID = Self->Subscribe(Callback);
        Callback(Item);
        *Result = MakeShared<Gs2::Core::Domain::CallbackID>(ID);
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAcceptVersionAccessTokenDomain::FSubscribeWithInitialCallTask>> FAcceptVersionAccessTokenDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Version::Model::FAcceptVersionPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    void FAcceptVersionAccessTokenDomain::Invalidate()
    {
        const auto SourceToken = AccessToken;
        Gs2::Version::Model::Cache::FAcceptVersionCache::Delete(
            Gs2->Cache,
            NamespaceName,
            SourceToken.IsValid() ? SourceToken->GetUserId() : TOptional<FString>(),
            VersionName,
            SourceToken.IsValid() ? SourceToken->GetTimeOffset() : TOptional<int32>()
        );
    }

    Gs2::Core::Domain::CallbackID FAcceptVersionAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Version::Model::FAcceptVersionPtr)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Version::Domain::FGs2VersionDomain> WeakService = Service;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryVersionName = VersionName;
        const auto SourceToken = AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid()
            ? TOptional<FString>(SourceToken->GetUserId())
            : TOptional<FString>();
        const int32 RegisteredTimeOffset = SourceToken.IsValid() ? SourceToken->GetTimeOffset().Get(0) : 0;

        const auto OwnerSubscriptionParentKey = Gs2::Version::Model::Cache::FAcceptVersionCache::CreateCacheParentKey(
            NamespaceName,
            RegisteredUserId,
            SourceToken.IsValid() ? SourceToken->GetTimeOffset() : TOptional<int32>()
        );
        const auto OwnerSubscriptionKey = Gs2::Version::Model::Cache::FAcceptVersionCache::CreateCacheKey(VersionName);
        return Gs2->Cache->Subscribe(
            Gs2::Version::Model::FAcceptVersion::TypeName,
            OwnerSubscriptionParentKey,
            OwnerSubscriptionKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Version::Model::FAcceptVersion>(obj));
            },
            [WeakGs2, WeakService, QueryNamespaceName, QueryVersionName, SourceToken, RegisteredUserId, RegisteredTimeOffset]()
            {
                const auto Owner = WeakGs2.Pin();
                const auto ServiceOwner = WeakService.Pin();
                if (!Owner.IsValid() || !SourceToken.IsValid() || !RegisteredUserId.IsSet())
                {
                    return;
                }
                const auto TokenSnapshot = MakeShared<Gs2::Auth::Model::FAccessToken>(*SourceToken);
                if (TokenSnapshot->GetUserId() != RegisteredUserId || TokenSnapshot->GetTimeOffset().Get(0) != RegisteredTimeOffset)
                {
                    return;
                }
                const auto Domain = MakeShared<FAcceptVersionAccessTokenDomain>(
                    Owner,
                    ServiceOwner,
                    QueryNamespaceName,
                    TokenSnapshot,
                    QueryVersionName
                );
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FAcceptVersionAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SourceToken = AccessToken;
        const auto OwnerSubscriptionParentKey = Gs2::Version::Model::Cache::FAcceptVersionCache::CreateCacheParentKey(
            NamespaceName,
            SourceToken.IsValid() ? SourceToken->GetUserId() : TOptional<FString>(),
            SourceToken.IsValid() ? SourceToken->GetTimeOffset() : TOptional<int32>()
        );
        const auto OwnerSubscriptionKey = Gs2::Version::Model::Cache::FAcceptVersionCache::CreateCacheKey(VersionName);
        Gs2->Cache->Unsubscribe(
            Gs2::Version::Model::FAcceptVersion::TypeName,
            OwnerSubscriptionParentKey,
            OwnerSubscriptionKey,
            CallbackID
        );
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
