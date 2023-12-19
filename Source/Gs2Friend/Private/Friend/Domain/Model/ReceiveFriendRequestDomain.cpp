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

#include "Friend/Domain/Model/ReceiveFriendRequest.h"
#include "Friend/Domain/Model/Namespace.h"
#include "Friend/Domain/Model/User.h"
#include "Friend/Domain/Model/UserAccessToken.h"
#include "Friend/Domain/Model/Profile.h"
#include "Friend/Domain/Model/ProfileAccessToken.h"
#include "Friend/Domain/Model/Friend.h"
#include "Friend/Domain/Model/FriendAccessToken.h"
#include "Friend/Domain/Model/BlackList.h"
#include "Friend/Domain/Model/BlackListAccessToken.h"
#include "Friend/Domain/Model/FollowUser.h"
#include "Friend/Domain/Model/FollowUserAccessToken.h"
#include "Friend/Domain/Model/FriendUser.h"
#include "Friend/Domain/Model/FriendUserAccessToken.h"
#include "Friend/Domain/Model/SendFriendRequest.h"
#include "Friend/Domain/Model/SendFriendRequestAccessToken.h"
#include "Friend/Domain/Model/ReceiveFriendRequest.h"
#include "Friend/Domain/Model/ReceiveFriendRequestAccessToken.h"
#include "Friend/Domain/Model/PublicProfile.h"
#include "Friend/Domain/Model/PublicProfileAccessToken.h"
#include "Friend/Domain/Model/FriendRequest.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Friend::Domain::Model
{

    FReceiveFriendRequestDomain::FReceiveFriendRequestDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Friend::Domain::FGs2FriendDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> FromUserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Friend::FGs2FriendRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        FromUserId(FromUserId),
        ParentKey(Gs2::Friend::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "ReceiveFriendRequest"
        ))
    {
    }

    FReceiveFriendRequestDomain::FReceiveFriendRequestDomain(
        const FReceiveFriendRequestDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        FromUserId(From.FromUserId),
        ParentKey(From.ParentKey)
    {

    }

    FReceiveFriendRequestDomain::FGetTask::FGetTask(
        const TSharedPtr<FReceiveFriendRequestDomain>& Self,
        const Request::FGetReceiveRequestByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FReceiveFriendRequestDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FReceiveFriendRequestDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Friend::Model::FFriendRequest>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithFromUserId(Self->FromUserId);
        const auto Future = Self->Client->GetReceiveRequestByUserId(
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
                const auto ParentKey = Gs2::Friend::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "ReceiveFriendRequest"
                );
                const auto Key = Gs2::Friend::Domain::Model::FReceiveFriendRequestDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetUserId()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Friend::Model::FFriendRequest::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FReceiveFriendRequestDomain::FGetTask>> FReceiveFriendRequestDomain::Get(
        Request::FGetReceiveRequestByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FReceiveFriendRequestDomain::FAcceptTask::FAcceptTask(
        const TSharedPtr<FReceiveFriendRequestDomain>& Self,
        const Request::FAcceptRequestByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FReceiveFriendRequestDomain::FAcceptTask::FAcceptTask(
        const FAcceptTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FReceiveFriendRequestDomain::FAcceptTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Friend::Domain::Model::FReceiveFriendRequestDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithFromUserId(Self->FromUserId);
        const auto Future = Self->Client->AcceptRequestByUserId(
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
                const auto ParentKey = Gs2::Friend::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "ReceiveFriendRequest"
                );
                const auto Key = Gs2::Friend::Domain::Model::FReceiveFriendRequestDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetUserId()
                );
                Self->Gs2->Cache->Delete(Gs2::Friend::Model::FFriendRequest::TypeName, ParentKey, Key);
            }
            Self->Gs2->Cache->ClearListCache(
                Gs2::Friend::Model::FFriendRequest::TypeName,
                Gs2::Friend::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->FromUserId,
                    "SendFriendRequest"
                )
            );
            Self->Gs2->Cache->ClearListCache(
                Gs2::Friend::Model::FFriendRequest::TypeName,
                Gs2::Friend::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "ReceiveFriendRequest"
                )
            );
            Self->Gs2->Cache->ClearListCache(
                Gs2::Friend::Model::FFriendUser::TypeName,
                Gs2::Friend::Domain::Model::FFriendDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    FString("True"),
                    "FriendUser"
                )
            );
            Self->Gs2->Cache->ClearListCache(
                Gs2::Friend::Model::FFriendUser::TypeName,
                Gs2::Friend::Domain::Model::FFriendDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    FString("False"),
                    "FriendUser"
                )
            );
        }
        auto Domain = MakeShared<Gs2::Friend::Domain::Model::FReceiveFriendRequestDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetUserId(),
            Self->FromUserId
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FReceiveFriendRequestDomain::FAcceptTask>> FReceiveFriendRequestDomain::Accept(
        Request::FAcceptRequestByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FAcceptTask>>(this->AsShared(), Request);
    }

    FReceiveFriendRequestDomain::FRejectTask::FRejectTask(
        const TSharedPtr<FReceiveFriendRequestDomain>& Self,
        const Request::FRejectRequestByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FReceiveFriendRequestDomain::FRejectTask::FRejectTask(
        const FRejectTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FReceiveFriendRequestDomain::FRejectTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Friend::Domain::Model::FReceiveFriendRequestDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithFromUserId(Self->FromUserId);
        const auto Future = Self->Client->RejectRequestByUserId(
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
                const auto ParentKey = Gs2::Friend::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "ReceiveFriendRequest"
                );
                const auto Key = Gs2::Friend::Domain::Model::FReceiveFriendRequestDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetUserId()
                );
                Self->Gs2->Cache->Delete(Gs2::Friend::Model::FFriendRequest::TypeName, ParentKey, Key);
            }
            Self->Gs2->Cache->ClearListCache(
                Gs2::Friend::Model::FFriendRequest::TypeName,
                Gs2::Friend::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->FromUserId,
                    "SendFriendRequest"
                )
            );
            Self->Gs2->Cache->ClearListCache(
                Gs2::Friend::Model::FFriendRequest::TypeName,
                Gs2::Friend::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "ReceiveFriendRequest"
                )
            );
            Self->Gs2->Cache->ClearListCache(
                Gs2::Friend::Model::FFriendUser::TypeName,
                Gs2::Friend::Domain::Model::FFriendDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    FString("True"),
                    "FriendUser"
                )
            );
            Self->Gs2->Cache->ClearListCache(
                Gs2::Friend::Model::FFriendUser::TypeName,
                Gs2::Friend::Domain::Model::FFriendDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    FString("False"),
                    "FriendUser"
                )
            );
        }
        auto Domain = MakeShared<Gs2::Friend::Domain::Model::FReceiveFriendRequestDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetUserId(),
            Self->FromUserId
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FReceiveFriendRequestDomain::FRejectTask>> FReceiveFriendRequestDomain::Reject(
        Request::FRejectRequestByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FRejectTask>>(this->AsShared(), Request);
    }

    FString FReceiveFriendRequestDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> FromUserId,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (FromUserId.IsSet() ? *FromUserId : "null") + ":" +
            ChildType;
    }

    FString FReceiveFriendRequestDomain::CreateCacheKey(
        TOptional<FString> FromUserId
    )
    {
        return FString("") +
            (FromUserId.IsSet() ? *FromUserId : "null");
    }

    FReceiveFriendRequestDomain::FModelTask::FModelTask(
        const TSharedPtr<FReceiveFriendRequestDomain> Self
    ): Self(Self)
    {

    }

    FReceiveFriendRequestDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FReceiveFriendRequestDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Friend::Model::FFriendRequest>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Friend::Model::FFriendRequest> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Friend::Model::FFriendRequest>(
            Self->ParentKey,
            Gs2::Friend::Domain::Model::FReceiveFriendRequestDomain::CreateCacheKey(
                Self->FromUserId
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Friend::Request::FGetReceiveRequestByUserIdRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Friend::Domain::Model::FReceiveFriendRequestDomain::CreateCacheKey(
                    Self->FromUserId
                );
                Self->Gs2->Cache->Put(
                    Gs2::Friend::Model::FFriendRequest::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "friendRequest")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Friend::Model::FFriendRequest>(
                Self->ParentKey,
                Gs2::Friend::Domain::Model::FReceiveFriendRequestDomain::CreateCacheKey(
                    Self->FromUserId
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FReceiveFriendRequestDomain::FModelTask>> FReceiveFriendRequestDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FReceiveFriendRequestDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FReceiveFriendRequestDomain::Subscribe(
        TFunction<void(Gs2::Friend::Model::FFriendRequestPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Friend::Model::FFriendRequest::TypeName,
            ParentKey,
            Gs2::Friend::Domain::Model::FReceiveFriendRequestDomain::CreateCacheKey(
                FromUserId
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Friend::Model::FFriendRequest>(obj));
            }
        );
    }

    void FReceiveFriendRequestDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Friend::Model::FFriendRequest::TypeName,
            ParentKey,
            Gs2::Friend::Domain::Model::FReceiveFriendRequestDomain::CreateCacheKey(
                FromUserId
            ),
            CallbackID
        );
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

