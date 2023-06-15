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

#include "Experience/Domain/Model/ExperienceModel.h"
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

    FExperienceModelDomain::FExperienceModelDomain(
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
            "ExperienceModel"
        ))
    {
    }

    FExperienceModelDomain::FExperienceModelDomain(
        const FExperienceModelDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FExperienceModelDomain::FGetTask::FGetTask(
        const TSharedPtr<FExperienceModelDomain> Self,
        const Request::FGetExperienceModelRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FExperienceModelDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FExperienceModelDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Experience::Model::FExperienceModel>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithExperienceName(Self->ExperienceName);
        const auto Future = Self->Client->GetExperienceModel(
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
                    "ExperienceModel"
                );
                const auto Key = Gs2::Experience::Domain::Model::FExperienceModelDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Experience::Model::FExperienceModel::TypeName,
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

    TSharedPtr<FAsyncTask<FExperienceModelDomain::FGetTask>> FExperienceModelDomain::Get(
        Request::FGetExperienceModelRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FExperienceModelDomain::CreateCacheParentKey(
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

    FString FExperienceModelDomain::CreateCacheKey(
        TOptional<FString> ExperienceName
    )
    {
        return FString() +
            (ExperienceName.IsSet() ? *ExperienceName : "null");
    }

    FExperienceModelDomain::FModelTask::FModelTask(
        const TSharedPtr<FExperienceModelDomain> Self
    ): Self(Self)
    {

    }

    FExperienceModelDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FExperienceModelDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Experience::Model::FExperienceModel>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Experience::Model::FExperienceModel> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Experience::Model::FExperienceModel>(
            Self->ParentKey,
            Gs2::Experience::Domain::Model::FExperienceModelDomain::CreateCacheKey(
                Self->ExperienceName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Experience::Request::FGetExperienceModelRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Experience::Domain::Model::FExperienceModelDomain::CreateCacheKey(
                    Self->ExperienceName
                );
                Self->Cache->Put(
                    Gs2::Experience::Model::FExperienceModel::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "experienceModel")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Cache->TryGet<Gs2::Experience::Model::FExperienceModel>(
                Self->ParentKey,
                Gs2::Experience::Domain::Model::FExperienceModelDomain::CreateCacheKey(
                    Self->ExperienceName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FExperienceModelDomain::FModelTask>> FExperienceModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FExperienceModelDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

