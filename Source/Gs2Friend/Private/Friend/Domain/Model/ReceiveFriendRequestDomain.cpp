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

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Friend::Domain::Model
{

    FReceiveFriendRequestDomain::FReceiveFriendRequestDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> FromUserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Friend::FGs2FriendRestClient>(Session)),
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
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FReceiveFriendRequestDomain::FGetTask::FGetTask(
        const TSharedPtr<FReceiveFriendRequestDomain> Self,
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
                Self->Cache->Put(
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
        const TSharedPtr<FReceiveFriendRequestDomain> Self,
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
                Self->Cache->Delete(Gs2::Friend::Model::FFriendRequest::TypeName, ParentKey, Key);
            }
            Self->Cache->ClearListCache(
                Gs2::Friend::Model::FFriendRequest::TypeName,
                Gs2::Friend::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->FromUserId,
                    "SendFriendRequest"
                )
            );
            Self->Cache->ClearListCache(
                Gs2::Friend::Model::FFriendRequest::TypeName,
                Gs2::Friend::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "ReceiveFriendRequest"
                )
            );
            Self->Cache->ClearListCache(
                Gs2::Friend::Model::FFriendUser::TypeName,
                Gs2::Friend::Domain::Model::FFriendDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    FString("True"),
                    "FriendUser"
                )
            );
            Self->Cache->ClearListCache(
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
            Self->Cache,
            Self->JobQueueDomain,
            Self->StampSheetConfiguration,
            Self->Session,
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
        const TSharedPtr<FReceiveFriendRequestDomain> Self,
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
                Self->Cache->Delete(Gs2::Friend::Model::FFriendRequest::TypeName, ParentKey, Key);
            }
            Self->Cache->ClearListCache(
                Gs2::Friend::Model::FFriendRequest::TypeName,
                Gs2::Friend::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->FromUserId,
                    "SendFriendRequest"
                )
            );
            Self->Cache->ClearListCache(
                Gs2::Friend::Model::FFriendRequest::TypeName,
                Gs2::Friend::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "ReceiveFriendRequest"
                )
            );
            Self->Cache->ClearListCache(
                Gs2::Friend::Model::FFriendUser::TypeName,
                Gs2::Friend::Domain::Model::FFriendDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    FString("True"),
                    "FriendUser"
                )
            );
            Self->Cache->ClearListCache(
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
            Self->Cache,
            Self->JobQueueDomain,
            Self->StampSheetConfiguration,
            Self->Session,
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
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (FromUserId.IsSet() ? *FromUserId : "null") + ":" +
            ChildType;
    }

    FString FReceiveFriendRequestDomain::CreateCacheKey(
        TOptional<FString> FromUserId
    )
    {
        return FString() +
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
        auto Value = Self->Cache->Get<Gs2::Friend::Model::FFriendRequest>(
            Self->ParentKey,
            Gs2::Friend::Domain::Model::FReceiveFriendRequestDomain::CreateCacheKey(
                Self->FromUserId
            )
        );
        if (Value == nullptr) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Friend::Request::FGetReceiveRequestByUserIdRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() == Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    if (Future->GetTask().Error()->Detail(0)->GetComponent() == "friendRequest")
                    {
                        Self->Cache->Delete(
                            Gs2::Friend::Model::FReceiveFriendRequest::TypeName,
                            Self->ParentKey,
                            Gs2::Friend::Domain::Model::FReceiveFriendRequestDomain::CreateCacheKey(
                                Self->FromUserId
                            )
                        );
                    }
                    else
                    {
                        return Future->GetTask().Error();
                    }
                }
                else
                {
                    return Future->GetTask().Error();
                }
            }
            Value = Self->Cache->Get<Gs2::Friend::Model::FFriendRequest>(
                Self->ParentKey,
                Gs2::Friend::Domain::Model::FReceiveFriendRequestDomain::CreateCacheKey(
                    Self->FromUserId
                )
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FReceiveFriendRequestDomain::FModelTask>> FReceiveFriendRequestDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FReceiveFriendRequestDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

