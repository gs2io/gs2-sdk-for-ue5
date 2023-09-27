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

#include "Experience/Domain/Model/ThresholdMaster.h"
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

    FThresholdMasterDomain::FThresholdMasterDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> ThresholdName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Experience::FGs2ExperienceRestClient>(Session)),
        NamespaceName(NamespaceName),
        ThresholdName(ThresholdName),
        ParentKey(Gs2::Experience::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "ThresholdMaster"
        ))
    {
    }

    FThresholdMasterDomain::FThresholdMasterDomain(
        const FThresholdMasterDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        ThresholdName(From.ThresholdName),
        ParentKey(From.ParentKey)
    {

    }

    FThresholdMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FThresholdMasterDomain> Self,
        const Request::FGetThresholdMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FThresholdMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FThresholdMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Experience::Model::FThresholdMaster>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithThresholdName(Self->ThresholdName);
        const auto Future = Self->Client->GetThresholdMaster(
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
                    "ThresholdMaster"
                );
                const auto Key = Gs2::Experience::Domain::Model::FThresholdMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Experience::Model::FThresholdMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FThresholdMasterDomain::FGetTask>> FThresholdMasterDomain::Get(
        Request::FGetThresholdMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FThresholdMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FThresholdMasterDomain> Self,
        const Request::FUpdateThresholdMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FThresholdMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FThresholdMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Experience::Domain::Model::FThresholdMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithThresholdName(Self->ThresholdName);
        const auto Future = Self->Client->UpdateThresholdMaster(
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
                    "ThresholdMaster"
                );
                const auto Key = Gs2::Experience::Domain::Model::FThresholdMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Experience::Model::FThresholdMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FThresholdMasterDomain::FUpdateTask>> FThresholdMasterDomain::Update(
        Request::FUpdateThresholdMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FThresholdMasterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FThresholdMasterDomain> Self,
        const Request::FDeleteThresholdMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FThresholdMasterDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FThresholdMasterDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Experience::Domain::Model::FThresholdMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithThresholdName(Self->ThresholdName);
        const auto Future = Self->Client->DeleteThresholdMaster(
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
                    "ThresholdMaster"
                );
                const auto Key = Gs2::Experience::Domain::Model::FThresholdMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Delete(Gs2::Experience::Model::FThresholdMaster::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FThresholdMasterDomain::FDeleteTask>> FThresholdMasterDomain::Delete(
        Request::FDeleteThresholdMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FThresholdMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> ThresholdName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (ThresholdName.IsSet() ? *ThresholdName : "null") + ":" +
            ChildType;
    }

    FString FThresholdMasterDomain::CreateCacheKey(
        TOptional<FString> ThresholdName
    )
    {
        return FString("") +
            (ThresholdName.IsSet() ? *ThresholdName : "null");
    }

    FThresholdMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FThresholdMasterDomain> Self
    ): Self(Self)
    {

    }

    FThresholdMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FThresholdMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Experience::Model::FThresholdMaster>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Experience::Model::FThresholdMaster> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Experience::Model::FThresholdMaster>(
            Self->ParentKey,
            Gs2::Experience::Domain::Model::FThresholdMasterDomain::CreateCacheKey(
                Self->ThresholdName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Experience::Request::FGetThresholdMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Experience::Domain::Model::FThresholdMasterDomain::CreateCacheKey(
                    Self->ThresholdName
                );
                Self->Cache->Put(
                    Gs2::Experience::Model::FThresholdMaster::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "thresholdMaster")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Cache->TryGet<Gs2::Experience::Model::FThresholdMaster>(
                Self->ParentKey,
                Gs2::Experience::Domain::Model::FThresholdMasterDomain::CreateCacheKey(
                    Self->ThresholdName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FThresholdMasterDomain::FModelTask>> FThresholdMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FThresholdMasterDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FThresholdMasterDomain::Subscribe(
        TFunction<void(Gs2::Experience::Model::FThresholdMasterPtr)> Callback
    )
    {
        return Cache->Subscribe(
            Gs2::Experience::Model::FThresholdMaster::TypeName,
            ParentKey,
            Gs2::Experience::Domain::Model::FThresholdMasterDomain::CreateCacheKey(
                ThresholdName
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Experience::Model::FThresholdMaster>(obj));
            }
        );
    }

    void FThresholdMasterDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Cache->Unsubscribe(
            Gs2::Experience::Model::FThresholdMaster::TypeName,
            ParentKey,
            Gs2::Experience::Domain::Model::FThresholdMasterDomain::CreateCacheKey(
                ThresholdName
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

