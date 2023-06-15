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

#include "Experience/Domain/Model/ExperienceModelMaster.h"
#include "Experience/Domain/Model/Namespace.h"
#include "Experience/Domain/Model/ExperienceModelMaster.h"
#include "Experience/Domain/Model/ExperienceModel.h"
#include "Experience/Domain/Model/ThresholdMaster.h"
#include "Experience/Domain/Model/CurrentExperienceMaster.h"
#include "Experience/Domain/Model/User.h"
#include "Experience/Domain/Model/UserAccessToken.h"
#include "Experience/Domain/Model/Status.h"
#include "Experience/Domain/Model/StatusAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Experience::Domain::Model
{

    FExperienceModelMasterDomain::FExperienceModelMasterDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> ExperienceName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Experience::FGs2ExperienceRestClient>(Session)),
        NamespaceName(NamespaceName),
        ExperienceName(ExperienceName),
        ParentKey(Gs2::Experience::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "ExperienceModelMaster"
        ))
    {
    }

    FExperienceModelMasterDomain::FExperienceModelMasterDomain(
        const FExperienceModelMasterDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FExperienceModelMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FExperienceModelMasterDomain> Self,
        const Request::FGetExperienceModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FExperienceModelMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FExperienceModelMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Experience::Model::FExperienceModelMaster>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithExperienceName(Self->ExperienceName);
        const auto Future = Self->Client->GetExperienceModelMaster(
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
                const auto ParentKey = Gs2::Experience::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "ExperienceModelMaster"
                );
                const auto Key = Gs2::Experience::Domain::Model::FExperienceModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Experience::Model::FExperienceModelMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FExperienceModelMasterDomain::FGetTask>> FExperienceModelMasterDomain::Get(
        Request::FGetExperienceModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FExperienceModelMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FExperienceModelMasterDomain> Self,
        const Request::FUpdateExperienceModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FExperienceModelMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FExperienceModelMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Experience::Domain::Model::FExperienceModelMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithExperienceName(Self->ExperienceName);
        const auto Future = Self->Client->UpdateExperienceModelMaster(
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
                const auto ParentKey = Gs2::Experience::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "ExperienceModelMaster"
                );
                const auto Key = Gs2::Experience::Domain::Model::FExperienceModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Experience::Model::FExperienceModelMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FExperienceModelMasterDomain::FUpdateTask>> FExperienceModelMasterDomain::Update(
        Request::FUpdateExperienceModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FExperienceModelMasterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FExperienceModelMasterDomain> Self,
        const Request::FDeleteExperienceModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FExperienceModelMasterDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FExperienceModelMasterDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Experience::Domain::Model::FExperienceModelMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithExperienceName(Self->ExperienceName);
        const auto Future = Self->Client->DeleteExperienceModelMaster(
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
                const auto ParentKey = Gs2::Experience::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "ExperienceModelMaster"
                );
                const auto Key = Gs2::Experience::Domain::Model::FExperienceModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Delete(Gs2::Experience::Model::FExperienceModelMaster::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FExperienceModelMasterDomain::FDeleteTask>> FExperienceModelMasterDomain::Delete(
        Request::FDeleteExperienceModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FExperienceModelMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> ExperienceName,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (ExperienceName.IsSet() ? *ExperienceName : "null") + ":" +
            ChildType;
    }

    FString FExperienceModelMasterDomain::CreateCacheKey(
        TOptional<FString> ExperienceName
    )
    {
        return FString() +
            (ExperienceName.IsSet() ? *ExperienceName : "null");
    }

    FExperienceModelMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FExperienceModelMasterDomain> Self
    ): Self(Self)
    {

    }

    FExperienceModelMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FExperienceModelMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Experience::Model::FExperienceModelMaster>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Experience::Model::FExperienceModelMaster> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Experience::Model::FExperienceModelMaster>(
            Self->ParentKey,
            Gs2::Experience::Domain::Model::FExperienceModelMasterDomain::CreateCacheKey(
                Self->ExperienceName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Experience::Request::FGetExperienceModelMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Experience::Domain::Model::FExperienceModelMasterDomain::CreateCacheKey(
                    Self->ExperienceName
                );
                Self->Cache->Put(
                    Gs2::Experience::Model::FExperienceModelMaster::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "experienceModelMaster")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Cache->TryGet<Gs2::Experience::Model::FExperienceModelMaster>(
                Self->ParentKey,
                Gs2::Experience::Domain::Model::FExperienceModelMasterDomain::CreateCacheKey(
                    Self->ExperienceName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FExperienceModelMasterDomain::FModelTask>> FExperienceModelMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FExperienceModelMasterDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

