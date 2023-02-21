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

#include "Deploy/Domain/Model/Output.h"
#include "Deploy/Domain/Model/Stack.h"
#include "Deploy/Domain/Model/Resource.h"
#include "Deploy/Domain/Model/Event.h"
#include "Deploy/Domain/Model/Output.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Deploy::Domain::Model
{

    FOutputDomain::FOutputDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> StackName,
        const TOptional<FString> OutputName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Deploy::FGs2DeployRestClient>(Session)),
        StackName(StackName),
        OutputName(OutputName),
        ParentKey(Gs2::Deploy::Domain::Model::FStackDomain::CreateCacheParentKey(
            StackName,
            "Output"
        ))
    {
    }

    FOutputDomain::FOutputDomain(
        const FOutputDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FOutputDomain::FGetTask::FGetTask(
        const TSharedPtr<FOutputDomain> Self,
        const Request::FGetOutputRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FOutputDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FOutputDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Deploy::Model::FOutput>> Result
    )
    {
        Request
            ->WithStackName(Self->StackName)
            ->WithOutputName(Self->OutputName);
        const auto Future = Self->Client->GetOutput(
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
                const auto ParentKey = Gs2::Deploy::Domain::Model::FStackDomain::CreateCacheParentKey(
                    Self->StackName,
                    "Output"
                );
                const auto Key = Gs2::Deploy::Domain::Model::FOutputDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put<Gs2::Deploy::Model::FOutput>(
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

    TSharedPtr<FAsyncTask<FOutputDomain::FGetTask>> FOutputDomain::Get(
        Request::FGetOutputRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FOutputDomain::CreateCacheParentKey(
        TOptional<FString> StackName,
        TOptional<FString> OutputName,
        FString ChildType
    )
    {
        return FString() +
            (StackName.IsSet() ? *StackName : "null") + ":" +
            (OutputName.IsSet() ? *OutputName : "null") + ":" +
            ChildType;
    }

    FString FOutputDomain::CreateCacheKey(
        TOptional<FString> OutputName
    )
    {
        return FString() +
            (OutputName.IsSet() ? *OutputName : "null");
    }

    FOutputDomain::FModelTask::FModelTask(
        const TSharedPtr<FOutputDomain> Self
    ): Self(Self)
    {

    }

    FOutputDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FOutputDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Deploy::Model::FOutput>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        auto Value = Self->Cache->Get<Gs2::Deploy::Model::FOutput>(
            Self->ParentKey,
            Gs2::Deploy::Domain::Model::FOutputDomain::CreateCacheKey(
                Self->OutputName
            )
        );
        if (Value == nullptr) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Deploy::Request::FGetOutputRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() == Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    if (Future->GetTask().Error()->Detail(0)->GetComponent() == "output")
                    {
                        Self->Cache->Delete<Gs2::Deploy::Model::FOutput>(
                            Self->ParentKey,
                            Gs2::Deploy::Domain::Model::FOutputDomain::CreateCacheKey(
                                Self->OutputName
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
            Value = Self->Cache->Get<Gs2::Deploy::Model::FOutput>(
                Self->ParentKey,
                Gs2::Deploy::Domain::Model::FOutputDomain::CreateCacheKey(
                    Self->OutputName
                )
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FOutputDomain::FModelTask>> FOutputDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FOutputDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

