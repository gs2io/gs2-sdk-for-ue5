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

#include "Version/Domain/Model/VersionModel.h"
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

    FVersionModelDomain::FVersionModelDomain(
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
            "VersionModel"
        ))
    {
    }

    FVersionModelDomain::FVersionModelDomain(
        const FVersionModelDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FVersionModelDomain::FGetTask::FGetTask(
        const TSharedPtr<FVersionModelDomain> Self,
        const Request::FGetVersionModelRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FVersionModelDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FVersionModelDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Version::Model::FVersionModel>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithVersionName(Self->VersionName);
        const auto Future = Self->Client->GetVersionModel(
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
                    "VersionModel"
                );
                const auto Key = Gs2::Version::Domain::Model::FVersionModelDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Version::Model::FVersionModel::TypeName,
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

    TSharedPtr<FAsyncTask<FVersionModelDomain::FGetTask>> FVersionModelDomain::Get(
        Request::FGetVersionModelRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FVersionModelDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> VersionName,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (VersionName.IsSet() ? *VersionName : "null") + ":" +
            ChildType;
    }

    FString FVersionModelDomain::CreateCacheKey(
        TOptional<FString> VersionName
    )
    {
        return FString() +
            (VersionName.IsSet() ? *VersionName : "null");
    }

    FVersionModelDomain::FModelTask::FModelTask(
        const TSharedPtr<FVersionModelDomain> Self
    ): Self(Self)
    {

    }

    FVersionModelDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FVersionModelDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Version::Model::FVersionModel>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        auto Value = Self->Cache->Get<Gs2::Version::Model::FVersionModel>(
            Self->ParentKey,
            Gs2::Version::Domain::Model::FVersionModelDomain::CreateCacheKey(
                Self->VersionName
            )
        );
        if (Value == nullptr) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Version::Request::FGetVersionModelRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() == Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    if (Future->GetTask().Error()->Detail(0)->GetComponent() == "versionModel")
                    {
                        Self->Cache->Delete(
                            Gs2::Version::Model::FVersionModel::TypeName,
                            Self->ParentKey,
                            Gs2::Version::Domain::Model::FVersionModelDomain::CreateCacheKey(
                                Self->VersionName
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
            Value = Self->Cache->Get<Gs2::Version::Model::FVersionModel>(
                Self->ParentKey,
                Gs2::Version::Domain::Model::FVersionModelDomain::CreateCacheKey(
                    Self->VersionName
                )
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FVersionModelDomain::FModelTask>> FVersionModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FVersionModelDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

