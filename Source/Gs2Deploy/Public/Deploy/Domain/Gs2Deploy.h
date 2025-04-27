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

// ReSharper disable CppUnusedIncludeDirective

#pragma once

#include "Core/Domain/Gs2Core.h"
#include "Core/Domain/Model/IssueTransactionEvent.h"
#include "JobQueue/Gs2JobQueue.h"
#include "Deploy/Gs2Deploy.h"

// Model
#include "Deploy/Domain/Model/Stack.h"
#include "Deploy/Domain/Model/Resource.h"
#include "Deploy/Domain/Model/Event.h"
#include "Deploy/Domain/Model/Output.h"

// Iterator
#include "Deploy/Domain/Iterator/DescribeStacksIterator.h"
#include "Deploy/Domain/Iterator/DescribeResourcesIterator.h"
#include "Deploy/Domain/Iterator/DescribeEventsIterator.h"
#include "Deploy/Domain/Iterator/DescribeOutputsIterator.h"

// Notification

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Deploy::Domain
{

    class GS2DEPLOY_API FGs2DeployDomain:
        public TSharedFromThis<FGs2DeployDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Gs2::Deploy::FGs2DeployRestClientPtr Client;

        public:
        TOptional<FString> UploadToken;
        TOptional<FString> UploadUrl;
        TOptional<FString> GetUploadToken() const
        {
            return UploadToken;
        }
        TOptional<FString> GetUploadUrl() const
        {
            return UploadUrl;
        }
    private:

        FString ParentKey;

    public:

        FGs2DeployDomain(
            const Core::Domain::FGs2Ptr& Gs2
            // ReSharper disable once CppMemberInitializersOrder
        );

        FGs2DeployDomain(
            const FGs2DeployDomain& From
        );

        class GS2DEPLOY_API FPreCreateStackTask final :
            public Gs2::Core::Util::TGs2Future<FGs2DeployDomain>,
            public TSharedFromThis<FPreCreateStackTask>
        {
            const TSharedPtr<FGs2DeployDomain> Self;
            const Request::FPreCreateStackRequestPtr Request;
        public:
            explicit FPreCreateStackTask(
                const TSharedPtr<FGs2DeployDomain>& Self,
                const Request::FPreCreateStackRequestPtr Request
            );

            FPreCreateStackTask(
                const FPreCreateStackTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<FGs2DeployDomain>> Result
            ) override;
        };
        friend FPreCreateStackTask;

        TSharedPtr<FAsyncTask<FPreCreateStackTask>> PreCreateStack(
            Request::FPreCreateStackRequestPtr Request
        );

        class GS2DEPLOY_API FCreateStackTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Deploy::Domain::Model::FStackDomain>,
            public TSharedFromThis<FCreateStackTask>
        {
            const TSharedPtr<FGs2DeployDomain> Self;
            const Request::FCreateStackRequestPtr Request;
        public:
            explicit FCreateStackTask(
                const TSharedPtr<FGs2DeployDomain>& Self,
                const Request::FCreateStackRequestPtr Request
            );

            FCreateStackTask(
                const FCreateStackTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Deploy::Domain::Model::FStackDomain>> Result
            ) override;
        };
        friend FCreateStackTask;

        TSharedPtr<FAsyncTask<FCreateStackTask>> CreateStack(
            Request::FCreateStackRequestPtr Request
        );

        class GS2DEPLOY_API FCreateStackFromGitHubTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Deploy::Domain::Model::FStackDomain>,
            public TSharedFromThis<FCreateStackFromGitHubTask>
        {
            const TSharedPtr<FGs2DeployDomain> Self;
            const Request::FCreateStackFromGitHubRequestPtr Request;
        public:
            explicit FCreateStackFromGitHubTask(
                const TSharedPtr<FGs2DeployDomain>& Self,
                const Request::FCreateStackFromGitHubRequestPtr Request
            );

            FCreateStackFromGitHubTask(
                const FCreateStackFromGitHubTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Deploy::Domain::Model::FStackDomain>> Result
            ) override;
        };
        friend FCreateStackFromGitHubTask;

        TSharedPtr<FAsyncTask<FCreateStackFromGitHubTask>> CreateStackFromGitHub(
            Request::FCreateStackFromGitHubRequestPtr Request
        );

        class GS2DEPLOY_API FPreValidateTask final :
            public Gs2::Core::Util::TGs2Future<FGs2DeployDomain>,
            public TSharedFromThis<FPreValidateTask>
        {
            const TSharedPtr<FGs2DeployDomain> Self;
            const Request::FPreValidateRequestPtr Request;
        public:
            explicit FPreValidateTask(
                const TSharedPtr<FGs2DeployDomain>& Self,
                const Request::FPreValidateRequestPtr Request
            );

            FPreValidateTask(
                const FPreValidateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<FGs2DeployDomain>> Result
            ) override;
        };
        friend FPreValidateTask;

        TSharedPtr<FAsyncTask<FPreValidateTask>> PreValidate(
            Request::FPreValidateRequestPtr Request
        );

        class GS2DEPLOY_API FValidateTask final :
            public Gs2::Core::Util::TGs2Future<FGs2DeployDomain>,
            public TSharedFromThis<FValidateTask>
        {
            const TSharedPtr<FGs2DeployDomain> Self;
            const Request::FValidateRequestPtr Request;
        public:
            explicit FValidateTask(
                const TSharedPtr<FGs2DeployDomain>& Self,
                const Request::FValidateRequestPtr Request
            );

            FValidateTask(
                const FValidateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<FGs2DeployDomain>> Result
            ) override;
        };
        friend FValidateTask;

        TSharedPtr<FAsyncTask<FValidateTask>> Validate(
            Request::FValidateRequestPtr Request
        );

        Gs2::Deploy::Domain::Iterator::FDescribeStacksIteratorPtr Stacks(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeStacks(
            TFunction<void()> Callback
        );

        void UnsubscribeStacks(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Deploy::Domain::Model::FStackDomain> Stack(
            const FString StackName
        );

        void UpdateCacheFromStampSheet(
            const FString Method,
            const FString Request,
            const FString Result
        );

        void UpdateCacheFromStampTask(
            const FString Method,
            const FString Request,
            const FString Result
        );

        void UpdateCacheFromJobResult(
            const FString Method,
            const Gs2::JobQueue::Model::FJobPtr Job,
            const Gs2::JobQueue::Model::FJobResultBodyPtr Result
        );

        void HandleNotification(
            const FString Action,
            const FString Payload
        );

        DECLARE_MULTICAST_DELEGATE_OneParam(FIssueTransactionDelegate, Gs2::Core::Domain::Model::FIssueTransactionEventPtr);
        FIssueTransactionDelegate OnIssueTransaction;
    };
    typedef TSharedPtr<FGs2DeployDomain> FGs2DeployDomainPtr;
}
