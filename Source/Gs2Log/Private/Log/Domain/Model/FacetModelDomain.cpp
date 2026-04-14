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

#include "Log/Domain/Model/FacetModel.h"
#include "Log/Domain/Model/Namespace.h"
#include "Log/Domain/Model/AccessLog.h"
#include "Log/Domain/Model/IssueStampSheetLog.h"
#include "Log/Domain/Model/ExecuteStampSheetLog.h"
#include "Log/Domain/Model/ExecuteStampTaskLog.h"
#include "Log/Domain/Model/InGameLog.h"
#include "Log/Domain/Model/InGameLogAccessToken.h"
#include "Log/Domain/Model/AccessLogWithTelemetry.h"
#include "Log/Domain/Model/User.h"
#include "Log/Domain/Model/UserAccessToken.h"
#include "Log/Domain/Model/Insight.h"
#include "Log/Domain/Model/FacetModel.h"
#include "Log/Domain/Model/Dashboard.h"
#include "Log/Domain/Model/LogEntry.h"
#include "Log/Domain/Model/MetricModel.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Log::Domain::Model
{

    FFacetModelDomain::FFacetModelDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Log::Domain::FGs2LogDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> Field
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Log::FGs2LogRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        Field(Field),
        ParentKey(Gs2::Log::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "FacetModel"
        ))
    {
    }

    FFacetModelDomain::FFacetModelDomain(
        const FFacetModelDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        Field(From.Field),
        ParentKey(From.ParentKey)
    {

    }

    FFacetModelDomain::FCreateTask::FCreateTask(
        const TSharedPtr<FFacetModelDomain>& Self,
        const Request::FCreateFacetModelRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FFacetModelDomain::FCreateTask::FCreateTask(
        const FCreateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FFacetModelDomain::FCreateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Log::Domain::Model::FFacetModelDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithField(Self->Field);
        const auto Future = Self->Client->CreateFacetModel(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel->GetItem() != nullptr)
        {
            const auto Key = Gs2::Log::Domain::Model::FFacetModelDomain::CreateCacheKey(
                ResultModel->GetItem()->GetField()
            );
            Self->Gs2->Cache->Put(
                Gs2::Log::Model::FFacetModel::TypeName,
                Self->ParentKey,
                Key,
                ResultModel->GetItem(),
                FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
            );
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FFacetModelDomain::FCreateTask>> FFacetModelDomain::Create(
        Request::FCreateFacetModelRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateTask>>(this->AsShared(), Request);
    }

    FFacetModelDomain::FGetTask::FGetTask(
        const TSharedPtr<FFacetModelDomain>& Self,
        const Request::FGetFacetModelRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FFacetModelDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FFacetModelDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Log::Model::FFacetModel>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithField(Self->Field);
        const auto Future = Self->Client->GetFacetModel(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FFacetModelDomain::FGetTask>> FFacetModelDomain::Get(
        Request::FGetFacetModelRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FFacetModelDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FFacetModelDomain>& Self,
        const Request::FUpdateFacetModelRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FFacetModelDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FFacetModelDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Log::Domain::Model::FFacetModelDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithField(Self->Field);
        const auto Future = Self->Client->UpdateFacetModel(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel->GetItem() != nullptr)
        {
            const auto Key = Gs2::Log::Domain::Model::FFacetModelDomain::CreateCacheKey(
                ResultModel->GetItem()->GetField()
            );
            Self->Gs2->Cache->Put(
                Gs2::Log::Model::FFacetModel::TypeName,
                Self->ParentKey,
                Key,
                ResultModel->GetItem(),
                FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
            );
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FFacetModelDomain::FUpdateTask>> FFacetModelDomain::Update(
        Request::FUpdateFacetModelRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FFacetModelDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FFacetModelDomain>& Self,
        const Request::FDeleteFacetModelRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FFacetModelDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FFacetModelDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Log::Domain::Model::FFacetModelDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithField(Self->Field);
        const auto Future = Self->Client->DeleteFacetModel(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel->GetItem() != nullptr)
        {
            const auto Key = Gs2::Log::Domain::Model::FFacetModelDomain::CreateCacheKey(
                ResultModel->GetItem()->GetField()
            );
            Self->Gs2->Cache->Delete(
                Gs2::Log::Model::FFacetModel::TypeName,
                Self->ParentKey,
                Key
            );
        }
        Self->Gs2->Cache->ClearListCache(
            Gs2::Log::Model::FFacetModel::TypeName,
            Self->ParentKey
        );
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FFacetModelDomain::FDeleteTask>> FFacetModelDomain::Delete(
        Request::FDeleteFacetModelRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FFacetModelDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> Field,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (Field.IsSet() ? *Field : "null") + ":" +
            ChildType;
    }

    FString FFacetModelDomain::CreateCacheKey(
        TOptional<FString> Field
    )
    {
        return FString("") +
            (Field.IsSet() ? *Field : "null");
    }

    FFacetModelDomain::FModelTask::FModelTask(
        const TSharedPtr<FFacetModelDomain> Self
    ): Self(Self)
    {

    }

    FFacetModelDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FFacetModelDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Log::Model::FFacetModel>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Log::Model::FFacetModel> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Log::Model::FFacetModel>(
            Self->ParentKey,
            Gs2::Log::Domain::Model::FFacetModelDomain::CreateCacheKey(
                Self->Field
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Log::Request::FGetFacetModelRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Log::Domain::Model::FFacetModelDomain::CreateCacheKey(
                    Self->Field
                );
                Self->Gs2->Cache->Put(
                    Gs2::Log::Model::FFacetModel::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "facetModel")
                {
                    return Future->GetTask().Error();
                }
            }
            else
            {
                Value = Future->GetTask().Result();
            }
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FFacetModelDomain::FModelTask>> FFacetModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FFacetModelDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FFacetModelDomain::Subscribe(
        TFunction<void(Gs2::Log::Model::FFacetModelPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Log::Model::FFacetModel::TypeName,
            ParentKey,
            Gs2::Log::Domain::Model::FFacetModelDomain::CreateCacheKey(
                Field
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Log::Model::FFacetModel>(obj));
            }
        );
    }

    void FFacetModelDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Log::Model::FFacetModel::TypeName,
            ParentKey,
            Gs2::Log::Domain::Model::FFacetModelDomain::CreateCacheKey(
                Field
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

