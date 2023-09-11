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
#include "Version/Domain/Model/AcceptVersion.h"
#include "Version/Domain/Model/Namespace.h"
#include "Version/Domain/Model/VersionModelMaster.h"
#include "Version/Domain/Model/VersionModel.h"
#include "Version/Domain/Model/AcceptVersion.h"
#include "Version/Domain/Model/AcceptVersionAccessToken.h"
#include "Version/Domain/Model/Checker.h"
#include "Version/Domain/Model/CheckerAccessToken.h"
#include "Version/Domain/Model/CurrentVersionMaster.h"
#include "Version/Domain/Model/User.h"
#include "Version/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Version::Domain::Model
{

    FAcceptVersionAccessTokenDomain::FAcceptVersionAccessTokenDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken,
        const TOptional<FString> VersionName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Version::FGs2VersionRestClient>(Session)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        VersionName(VersionName),
        ParentKey(Gs2::Version::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "AcceptVersion"
        ))
    {
    }

    FAcceptVersionAccessTokenDomain::FAcceptVersionAccessTokenDomain(
        const FAcceptVersionAccessTokenDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        VersionName(From.VersionName),
        ParentKey(From.ParentKey)
    {

    }

    FAcceptVersionAccessTokenDomain::FAcceptTask::FAcceptTask(
        const TSharedPtr<FAcceptVersionAccessTokenDomain> Self,
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
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithVersionName(Self->VersionName);
        const auto Future = Self->Client->Accept(
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
                    Self->UserId(),
                    "AcceptVersion"
                );
                const auto Key = Gs2::Version::Domain::Model::FAcceptVersionDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetVersionName()
                );
                Self->Cache->Put(
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

    TSharedPtr<FAsyncTask<FAcceptVersionAccessTokenDomain::FAcceptTask>> FAcceptVersionAccessTokenDomain::Accept(
        Request::FAcceptRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FAcceptTask>>(this->AsShared(), Request);
    }

    FAcceptVersionAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FAcceptVersionAccessTokenDomain> Self,
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
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithVersionName(Self->VersionName);
        const auto Future = Self->Client->GetAcceptVersion(
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
                    Self->UserId(),
                    "AcceptVersion"
                );
                const auto Key = Gs2::Version::Domain::Model::FAcceptVersionDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetVersionName()
                );
                Self->Cache->Put(
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

    TSharedPtr<FAsyncTask<FAcceptVersionAccessTokenDomain::FGetTask>> FAcceptVersionAccessTokenDomain::Get(
        Request::FGetAcceptVersionRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FAcceptVersionAccessTokenDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FAcceptVersionAccessTokenDomain> Self,
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
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithVersionName(Self->VersionName);
        const auto Future = Self->Client->DeleteAcceptVersion(
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
                    Self->UserId(),
                    "AcceptVersion"
                );
                const auto Key = Gs2::Version::Domain::Model::FAcceptVersionDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetVersionName()
                );
                Self->Cache->Delete(Gs2::Version::Model::FAcceptVersion::TypeName, ParentKey, Key);
            }
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
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Version::Model::FAcceptVersion> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Version::Model::FAcceptVersion>(
            Self->ParentKey,
            Gs2::Version::Domain::Model::FAcceptVersionDomain::CreateCacheKey(
                Self->VersionName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Version::Request::FGetAcceptVersionRequest>()
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
                Self->Cache->Put(
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
            Self->Cache->TryGet<Gs2::Version::Model::FAcceptVersion>(
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

    TSharedPtr<FAsyncTask<FAcceptVersionAccessTokenDomain::FModelTask>> FAcceptVersionAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FAcceptVersionAccessTokenDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

