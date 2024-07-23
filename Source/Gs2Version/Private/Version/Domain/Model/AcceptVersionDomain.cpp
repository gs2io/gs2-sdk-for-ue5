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
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Version::Domain::Model
{

    FAcceptVersionDomain::FAcceptVersionDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Version::Domain::FGs2VersionDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> VersionName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Version::FGs2VersionRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        VersionName(VersionName),
        ParentKey(Gs2::Version::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "AcceptVersion"
        ))
    {
    }

    FAcceptVersionDomain::FAcceptVersionDomain(
        const FAcceptVersionDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        VersionName(From.VersionName),
        ParentKey(From.ParentKey)
    {

    }

    FAcceptVersionDomain::FAcceptTask::FAcceptTask(
        const TSharedPtr<FAcceptVersionDomain>& Self,
        const Request::FAcceptByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FAcceptVersionDomain::FAcceptTask::FAcceptTask(
        const FAcceptTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FAcceptVersionDomain::FAcceptTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Version::Domain::Model::FAcceptVersionDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithVersionName(Self->VersionName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->AcceptByUserId(
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
                const auto ParentKey = Gs2::Version::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "AcceptVersion"
                );
                const auto Key = Gs2::Version::Domain::Model::FAcceptVersionDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetVersionName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Version::Model::FAcceptVersion::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAcceptVersionDomain::FAcceptTask>> FAcceptVersionDomain::Accept(
        Request::FAcceptByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FAcceptTask>>(this->AsShared(), Request);
    }

    FAcceptVersionDomain::FGetTask::FGetTask(
        const TSharedPtr<FAcceptVersionDomain>& Self,
        const Request::FGetAcceptVersionByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FAcceptVersionDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FAcceptVersionDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Version::Model::FAcceptVersion>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithVersionName(Self->VersionName);
        const auto Future = Self->Client->GetAcceptVersionByUserId(
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
                const auto ParentKey = Gs2::Version::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "AcceptVersion"
                );
                const auto Key = Gs2::Version::Domain::Model::FAcceptVersionDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetVersionName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Version::Model::FAcceptVersion::TypeName,
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

    TSharedPtr<FAsyncTask<FAcceptVersionDomain::FGetTask>> FAcceptVersionDomain::Get(
        Request::FGetAcceptVersionByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FAcceptVersionDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FAcceptVersionDomain>& Self,
        const Request::FDeleteAcceptVersionByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FAcceptVersionDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FAcceptVersionDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Version::Domain::Model::FAcceptVersionDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithVersionName(Self->VersionName);
        const auto Future = Self->Client->DeleteAcceptVersionByUserId(
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
                const auto ParentKey = Gs2::Version::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "AcceptVersion"
                );
                const auto Key = Gs2::Version::Domain::Model::FAcceptVersionDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetVersionName()
                );
                Self->Gs2->Cache->Delete(Gs2::Version::Model::FAcceptVersion::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAcceptVersionDomain::FDeleteTask>> FAcceptVersionDomain::Delete(
        Request::FDeleteAcceptVersionByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FAcceptVersionDomain::CreateCacheParentKey(
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

    FString FAcceptVersionDomain::CreateCacheKey(
        TOptional<FString> VersionName
    )
    {
        return FString("") +
            (VersionName.IsSet() ? *VersionName : "null");
    }

    FAcceptVersionDomain::FModelTask::FModelTask(
        const TSharedPtr<FAcceptVersionDomain> Self
    ): Self(Self)
    {

    }

    FAcceptVersionDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FAcceptVersionDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Version::Model::FAcceptVersion>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Version::Model::FAcceptVersion> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Version::Model::FAcceptVersion>(
            Self->ParentKey,
            Gs2::Version::Domain::Model::FAcceptVersionDomain::CreateCacheKey(
                Self->VersionName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Version::Request::FGetAcceptVersionByUserIdRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Version::Domain::Model::FAcceptVersionDomain::CreateCacheKey(
                    Self->VersionName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Version::Model::FAcceptVersion::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "acceptVersion")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Version::Model::FAcceptVersion>(
                Self->ParentKey,
                Gs2::Version::Domain::Model::FAcceptVersionDomain::CreateCacheKey(
                    Self->VersionName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAcceptVersionDomain::FModelTask>> FAcceptVersionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FAcceptVersionDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FAcceptVersionDomain::Subscribe(
        TFunction<void(Gs2::Version::Model::FAcceptVersionPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Version::Model::FAcceptVersion::TypeName,
            ParentKey,
            Gs2::Version::Domain::Model::FAcceptVersionDomain::CreateCacheKey(
                VersionName
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Version::Model::FAcceptVersion>(obj));
            }
        );
    }

    void FAcceptVersionDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Version::Model::FAcceptVersion::TypeName,
            ParentKey,
            Gs2::Version::Domain::Model::FAcceptVersionDomain::CreateCacheKey(
                VersionName
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

