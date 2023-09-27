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

#include "Version/Domain/Model/VersionModelMaster.h"
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

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Version::Domain::Model
{

    FVersionModelMasterDomain::FVersionModelMasterDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> VersionName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Version::FGs2VersionRestClient>(Session)),
        NamespaceName(NamespaceName),
        VersionName(VersionName),
        ParentKey(Gs2::Version::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "VersionModelMaster"
        ))
    {
    }

    FVersionModelMasterDomain::FVersionModelMasterDomain(
        const FVersionModelMasterDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        VersionName(From.VersionName),
        ParentKey(From.ParentKey)
    {

    }

    FVersionModelMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FVersionModelMasterDomain> Self,
        const Request::FGetVersionModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FVersionModelMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FVersionModelMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Version::Model::FVersionModelMaster>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithVersionName(Self->VersionName);
        const auto Future = Self->Client->GetVersionModelMaster(
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
                const auto ParentKey = Gs2::Version::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "VersionModelMaster"
                );
                const auto Key = Gs2::Version::Domain::Model::FVersionModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Version::Model::FVersionModelMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FVersionModelMasterDomain::FGetTask>> FVersionModelMasterDomain::Get(
        Request::FGetVersionModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FVersionModelMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FVersionModelMasterDomain> Self,
        const Request::FUpdateVersionModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FVersionModelMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FVersionModelMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Version::Domain::Model::FVersionModelMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithVersionName(Self->VersionName);
        const auto Future = Self->Client->UpdateVersionModelMaster(
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
                const auto ParentKey = Gs2::Version::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "VersionModelMaster"
                );
                const auto Key = Gs2::Version::Domain::Model::FVersionModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Version::Model::FVersionModelMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FVersionModelMasterDomain::FUpdateTask>> FVersionModelMasterDomain::Update(
        Request::FUpdateVersionModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FVersionModelMasterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FVersionModelMasterDomain> Self,
        const Request::FDeleteVersionModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FVersionModelMasterDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FVersionModelMasterDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Version::Domain::Model::FVersionModelMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithVersionName(Self->VersionName);
        const auto Future = Self->Client->DeleteVersionModelMaster(
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
                const auto ParentKey = Gs2::Version::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "VersionModelMaster"
                );
                const auto Key = Gs2::Version::Domain::Model::FVersionModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Delete(Gs2::Version::Model::FVersionModelMaster::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FVersionModelMasterDomain::FDeleteTask>> FVersionModelMasterDomain::Delete(
        Request::FDeleteVersionModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FVersionModelMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> VersionName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (VersionName.IsSet() ? *VersionName : "null") + ":" +
            ChildType;
    }

    FString FVersionModelMasterDomain::CreateCacheKey(
        TOptional<FString> VersionName
    )
    {
        return FString("") +
            (VersionName.IsSet() ? *VersionName : "null");
    }

    FVersionModelMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FVersionModelMasterDomain> Self
    ): Self(Self)
    {

    }

    FVersionModelMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FVersionModelMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Version::Model::FVersionModelMaster>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Version::Model::FVersionModelMaster> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Version::Model::FVersionModelMaster>(
            Self->ParentKey,
            Gs2::Version::Domain::Model::FVersionModelMasterDomain::CreateCacheKey(
                Self->VersionName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Version::Request::FGetVersionModelMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Version::Domain::Model::FVersionModelMasterDomain::CreateCacheKey(
                    Self->VersionName
                );
                Self->Cache->Put(
                    Gs2::Version::Model::FVersionModelMaster::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "versionModelMaster")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Cache->TryGet<Gs2::Version::Model::FVersionModelMaster>(
                Self->ParentKey,
                Gs2::Version::Domain::Model::FVersionModelMasterDomain::CreateCacheKey(
                    Self->VersionName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FVersionModelMasterDomain::FModelTask>> FVersionModelMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FVersionModelMasterDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FVersionModelMasterDomain::Subscribe(
        TFunction<void(Gs2::Version::Model::FVersionModelMasterPtr)> Callback
    )
    {
        return Cache->Subscribe(
            Gs2::Version::Model::FVersionModelMaster::TypeName,
            ParentKey,
            Gs2::Version::Domain::Model::FVersionModelMasterDomain::CreateCacheKey(
                VersionName
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Version::Model::FVersionModelMaster>(obj));
            }
        );
    }

    void FVersionModelMasterDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Cache->Unsubscribe(
            Gs2::Version::Model::FVersionModelMaster::TypeName,
            ParentKey,
            Gs2::Version::Domain::Model::FVersionModelMasterDomain::CreateCacheKey(
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

